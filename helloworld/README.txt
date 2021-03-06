------------------------------------------- DETENTION -------------------------------------------
                       by Logan Flurry, Kyle Saltzberg, Ani Minnick, Holly Carpenter

** TO DOWNLOAD **

Open Xfce terminal on lab machines
  cd /scratch/userid/
  git clone https://github.com/halkuponthegale/Detention.git
  

**TO COMPILE**

Prerequisites:
- CMAKE (www.cmake.org)
- SFML 2.4.2 (www.sfml-dev.org)
- About 420MB of memory space

Make a subdirectory 'Release' in Detention/helloworld/. In command line, navigate to 'Release' and type 'cmake ..' to generate a makefile.  If SFML is not installed in standard location, you will need to set the LIB and INCLUDE environment variables. For example if SFML is installed in ~/SFML, then you can adjust the environment variables (assuming linux and a BASH-shell) by:

export LIB=$LIB:~/SFML/lib
export INCLUDE=$INCLUDE:~/SFML/include

If SFML is installed, and the environment variables are correctly set, then running 'cmake ..' from 'Release' will produce something like:

-- The C compiler identification is GNU 4.8.5
-- The CXX compiler identification is GNU 4.8.5
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found SFML .. in /home/f85/username/SFML/include
-- Out-source building. Build type set to: RELEASE
-- Adding executable: gameApplication
-- Configuring done
-- Generating done
-- Build files have been written to: /scratch/userid/Detention/helloworld/Release

Now that the Makefile has been succesfully generated, you can compile with 'make'. This will produce a 'gameApplication' executable.

Type './gameApplication' to launch the executable. Enjoy!
