// $Id: commands.cpp,v 1.17 2018-01-25 14:02:55-08 - - $

#include "commands.h"
#include "debug.h"

command_hash cmd_hash {
   {"cat"   , fn_cat   },
   {"cd"    , fn_cd    },
   {"echo"  , fn_echo  },
   {"exit"  , fn_exit  },
   {"ls"    , fn_ls    },
   {"lsr"   , fn_lsr   },
   {"make"  , fn_make  },
   {"mkdir" , fn_mkdir },
   {"prompt", fn_prompt},
   {"pwd"   , fn_pwd   },
   {"rm"    , fn_rm    },
   {"rmr"    , fn_rmr    },
};

command_fn find_command_fn (const string& cmd) {
   // Note: value_type is pair<const key_type, mapped_type>
   // So: iterator->first is key_type (string)
   // So: iterator->second is mapped_type (command_fn)
   DEBUGF ('c', "[" << cmd << "]");
   const auto result = cmd_hash.find (cmd);
   if (result == cmd_hash.end()) {
      throw command_error (cmd + ": command not found");
   }
   return result->second;
}

command_error::command_error (const string& what):
            runtime_error (what) {
}

int exit_status_message() {
   int exit_status = exit_status::get();
   cout << execname() << ": exit(" << exit_status << ")" << endl;
   return exit_status;
}

//Need to get the last thing in the path
inode_ptr deal_with_path_ls(inode_ptr wd, const string& path){
   if (path == "/"){
      return wd;
   }
   else{
      wordvec parts = split(path, "/");
      inode_ptr current = wd;
      for (size_t i = 0; i != parts.size(); ++i){
         auto found = current->get_contents()->find(parts.at(i));
         if(found == nullptr){
            return nullptr;
         }else{
            current = found;
         }
         
      }
      return current;
   }
}

//Need to get second to last thing in path
inode_ptr deal_with_path_mk(inode_ptr wd, const string& path){
   if (path == "/"){
      return wd;
   }
   else{
      // split path to consider parts one at a time
      wordvec parts = split(path, "/");
      inode_ptr current = wd;
      // iterate over parts of path, if find returns nullptr
      for (size_t i = 0; i != parts.size() - 1; ++i){
         auto found = current->get_contents()->find(parts.at(i));
         if(found == nullptr){
            // no directory of this name
            return nullptr;
         }
         else{
            current = found;
         }
      }

      return current;
   }
}

void fn_cat (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   if(words.size() <= 1) {
      throw command_error("cat: no file specified");
   }
   inode_ptr final_path;
   for (vector<string>::const_iterator itor = words.begin();
         itor != words.end(); ++itor)
   {
      try{
         if(itor == words.begin()){++itor;} // skip first word
         // try to find ptr to file
         final_path = deal_with_path_ls(state._wd_(), *itor);
         if(final_path == nullptr){
            // not found
            throw file_error("cat: " + *itor + 
                             ": No such file or directory");
         }
         else if(final_path->inode_type() == file_type::DIRECTORY_TYPE)
         { //wrong type
            throw file_error("cat: " + *itor + ": Is a directory");
         }
         else{
            cout << final_path->get_contents()->readfile();
            if(final_path->size() != 0){
               cout << endl;
            }
         }
      }catch(file_error error){
         cerr << error.what() << endl;
         exit_status::set (EXIT_FAILURE);
         
      }
   }
}


void fn_cd (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   if (words.size() == 1){
      state.set_cwd(state._rt_());
   }
   else if(words.size() != 2){
      // bash doesn't mind but done for asg spec
      throw command_error
                ("cd: Too many operands");
   }
   else if (words.at(1)== "/"){
      // pathname / is root
      state.set_cwd(state._rt_());
   }
   else{
      inode_ptr final_dir = 
            deal_with_path_ls(state._wd_(), words.at(1));
      if(final_dir == nullptr){
         throw command_error
                ("cd: " + words.at(1) + ": No such file or directory");
      }
      else if(final_dir->inode_type() == file_type::PLAIN_TYPE)
         { //wrong type
            throw file_error
                        ("cd: " + words.at(1) + ": Not a directory");
         }
      else{
         state.set_cwd(final_dir);
      }
      
   }
   
}

void fn_echo (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   cout << word_range (words.cbegin() + 1, words.cend()) << endl;
}


void fn_exit (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   int ex_st = exit_status::get();
   if (words.size() != 1){
      ex_st = atoi(words.at(1).c_str());
      // non-numeric argument
      if (ex_st == 0 && words.at(1).at(0) != '0')
         ex_st = 127;
   }
   exit_status::set(ex_st);
   throw ysh_exit();
}

void fn_ls (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   
   inode_ptr final_path;
   if (words.size() == 1) {
      // no args, use working dir
      if (state._wd_() != state._rt_()){
         // working dir is not root,
         // need to get pathname for working directory
         string dirname = 
            state._rt_()->get_contents()->build_path(state._wd_());
         cout << dirname <<  ":" << endl;
      }
      else{
         // no args and at root
         cout << "/:" << endl;
      }
      // set final path to dir to print
      final_path = state._wd_();
   }
   // split here for multiple args
   else if (words.at(1)== "/"){
      // pathname / is root
      cout << "/:" << endl;
      final_path = state._rt_();
   }
   else if (words.size() != 1){
      // NEED TO DO MULTIPLE ARGS
      inode_ptr working_dir = state._wd_();
      final_path = deal_with_path_ls(working_dir, words.at(1));
      if(final_path == nullptr){
         throw file_error("ls: cannot access " + 
               words.at(1) + ": No such file or directory");
      }
      else{
         //do a more norm itor go to parts -1
         cout << words.at(1) <<":" << endl;
      }

   }
   final_path->print_from();
   // check if ls has operands(directories)
}

void fn_lsr (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   inode_ptr final_path;
   string dirname;
   vector<inode_ptr> subdirs;
   if (words.size() == 1) {
      // no args, use working dir
      if (state._wd_() != state._rt_()){
         // working dir is not root,
         // need to get pathname for working directory
         dirname = 
            state._rt_()->get_contents()->build_path(state._wd_());
      }
      else{
         //no args and at root
         dirname = "";
      }
      // set final path to dir to print
      final_path = state._wd_();
      // get subdirs of current working dir
      subdirs = 
         final_path->get_contents()->get_subdirs();

   }
   else if (words.at(1)== "/"){
      //need to print from root
      dirname = "";
      final_path = state._rt_();
      subdirs = 
         final_path->get_contents()->get_subdirs();
   }
   else if (words.size() != 1){
      // NEED TO DO MULTIPLE ARGS
      inode_ptr working_dir = state._wd_();
      final_path = deal_with_path_ls(working_dir, words.at(1));
      if(final_path == nullptr){
         throw file_error("ls: cannot access " + 
               words.at(1) + ": No such file or directory");
      }
      else{
         subdirs = 
            final_path->get_contents()->get_subdirs();
         wordvec parts = split(words.at(1), "/");
         //make an itor to go to parts -1
         vector<string>::const_iterator itor = words.end();
         --itor;

         dirname = words.at(1);
      }

   }
   if(dirname == ""){
      cout << "/:" << endl;
   }else{
      cout << dirname <<  ":" << endl;
   }
   
   final_path->print_from();

   for(auto itor : subdirs){
      dirname = itor->get_contents()->build_path(itor);
      //cout << dirname <<  ":" << endl;
      itor->get_contents()->print_recursive();
   }
}

void fn_make (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   // default parent for new file is working dir
   inode_ptr new_fle, parent_ptr;
   parent_ptr = state._wd_();

   if (words.at(1).find("/") == string::npos){
      // no path to deal with
      new_fle = parent_ptr->get_contents()->mkfile(words.at(1));
   }
   else{
      // path to deal with, find ptr to parent directory for new file
      parent_ptr = deal_with_path_mk(parent_ptr, words.at(1));
      // no parent directory found, bad pathname
      if(parent_ptr == nullptr){
         throw file_error("make: cannot create directory '" + 
                  words.at(1) + "': No such file or directory");
      }

      // extract filename from pathname
      vector<string> path_parts = split(words.at(1), "/");
      auto parts_itor = path_parts.end();
      --parts_itor;
      // make empty file pointer
      new_fle = parent_ptr->get_contents()->mkfile(*parts_itor);
   }
   
   // pointer to empty file in directory
   // put the words into the file
   try{ new_fle->get_contents()->writefile(words);  } 
   catch (file_error error){
      throw file_error("make: " + words.at(1) + ": " + error.what());
   }
}



void fn_mkdir (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   // default parent for new dir is working dir
   inode_ptr new_dir, parent_ptr;
   parent_ptr = state._wd_();

   // if words.at(1) doesnt have a slash
   // there is no need to deal with paths
   if (words.at(1).find("/") == string::npos){
      new_dir = parent_ptr->get_contents()->mkdir(words.at(1));
   }
   else{
      // path to deal with, find ptr to parent directory for new file
      parent_ptr = deal_with_path_mk(parent_ptr, words.at(1));
      // no parent directory found, bad pathname
      DEBUGF('x',"parent_ptr = " << parent_ptr << endl);
      if(parent_ptr == nullptr){
         throw file_error("mkdir: cannot create directory '" + 
                        words.at(1) + "': No such file or directory");
      }

      // extract new dirname from pathname
      vector<string> path_parts = split(words.at(1), "/");
      auto parts_itor = path_parts.end();
      --parts_itor;
      // make empty dir pointer
      new_dir = parent_ptr->get_contents()->mkdir(*parts_itor);
   }

   // need to connect child to parent
   new_dir->get_contents()->set_parent(parent_ptr);
   new_dir->get_contents()->set_dot(new_dir);  
}

void fn_prompt (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   state.prompt(words);
}

void fn_pwd (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   cout << (state._rt_() == state._wd_() ? "/" :
      state._wd_()->get_contents()->build_path(state._wd_())) << endl;
}

void fn_rm (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);

   // get to parent pointer, remove final thing in path from parentInode
   // then disown pointer to thing

   // error for pathname to not exist
   // if directory, must be empty, else error


   if(words.size() <= 1) {
      throw command_error("rm: no file specified");
   }
   inode_ptr parent_ptr, rm_me_ptr;
   try{
         // try to find ptr to file
      parent_ptr = deal_with_path_mk(state._wd_(), words.at(1));
      rm_me_ptr = deal_with_path_ls(state._wd_(), words.at(1));
      if(parent_ptr == nullptr or rm_me_ptr == nullptr){
         // not found
         throw file_error("rm: " + words.at(1) + 
                          ": No such file or directory");
      }
      else{
         // extract new dirname from pathname
         /*vector<string> path_parts_vec = split(words.at(1), "/");
         auto path_part = path_parts_vec.end();
         --path_part;
         rm_me_ptr = parent_ptr->find(*path_part); */
         string name = parent_ptr->find_name(rm_me_ptr);
         if (rm_me_ptr->size() != 2
             and rm_me_ptr->inode_type() == file_type::DIRECTORY_TYPE)
         {
            throw file_error("rm: " + words.at(1)  
                               +  ": is a non-empty directory");
         }
         parent_ptr->rm(name);
      }
   }catch(file_error error){
      cerr << error.what() << endl;
      exit_status::set (EXIT_FAILURE);
      
   }
}


void fn_rmr (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   // get to parent pointer, remove final thing in path from parentInode
   // then disown pointer to thing

   // error for pathname to not exist
   // if directory, must be empty, else error
   #define _FILE_DNE_ ": No such file or directory"

   if(words.size() <= 1) {
      throw command_error("rmr: no file specified");
   }
   inode_ptr parent_ptr, rm_me_ptr;
   try{
         // try to find ptr to file
      parent_ptr = deal_with_path_mk(state._wd_(), words.at(1));
      rm_me_ptr = deal_with_path_ls(state._wd_(), words.at(1));
      if(parent_ptr == nullptr or rm_me_ptr == nullptr){
         // not found
         throw file_error("rmr: " + words.at(1) + _FILE_DNE_);
      }
      else{
         // extract new dirname from pathname
        /* vector<string> path_parts_vec = split(words.at(1), "/");
         auto path_part = path_parts_vec.end();
         --path_part;
         rm_me_ptr = parent_ptr->find(*path_part); */

         string name = parent_ptr->find_name(rm_me_ptr);
         if (rm_me_ptr->inode_type() == file_type::DIRECTORY_TYPE)
         {
            parent_ptr->rm(name);
         }

      }
   }catch(file_error error){
      cerr << error.what() << endl;
      exit_status::set (EXIT_FAILURE);
      
   }
}

