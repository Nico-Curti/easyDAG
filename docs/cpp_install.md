## C++ Installation

1) Follow your system prerequisites (below)

2) Clone the `easyDAG` package from this repository, or download a stable release

```bash
git clone https://github.com/Nico-Curti/easyDAG.git
cd easyDAG
```

3) `easyDAG` could be built with CMake and Make or with the *build* scripts in the project.
Example:

**Unix OS:**
```bash
./build.sh
```

**Windows OS:**
```Powershell
PS \>                 ./build.ps1
```

## Installation

### Ubuntu

1) Define a work folder, which we will call WORKSPACE in this tutorial: this could be a "Code" folder in our home, a "c++" folder on our desktop, whatever you want. Create it if you don't already have, using your favourite method (mkdir in bash, or from the graphical interface of your distribution). We will now define an environment variable to tell the system where our folder is. Please note down the full path of this folder, which will look like `/home/$(whoami)/code/`

```bash
echo -e "\n export WORKSPACE=/full/path/to/my/folder \n" >> ~/.bashrc
source ~/.bashrc
```

2) Open a Bash terminal and type the following commands to install all the prerequisites.

```bash
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install -y gcc-8 g++-8

wget --no-check-certificate https://cmake.org/files/v3.13/cmake-3.13.1-Linux-x86_64.tar.gz
tar -xzf cmake-3.13.1-Linux-x86_64.tar.gz
export PATH=$PWD/cmake-3.13.1-Linux-x86_64/bin:$PATH

sudo apt-get install -y make git dos2unix ninja-build
git config --global core.autocrlf input
git clone https://github.com/physycom/sysconfig
```

3) Build the project with CMake (enable or disable OMP with the define **-DOMP**:

```bash
cd $WORKSPACE
git clone https://github.com/Nico-Curti/easyDAG
cd easyDAG

mkdir -p build
cd build

cmake -DOMP=ON ..
make -j
cmake --build . --target install
cd ..
```

### macOS

1) If not already installed, install the XCode Command Line Tools, typing this command in a terminal:

```bash
xcode-select --install
```

2) If not already installed, install Homebrew following the [official guide](https://brew.sh/index_it.html).

3) Open the terminal and type these commands

```bash
brew update
brew upgrade
brew install gcc@8
brew install cmake make git ninja
```

4) Define a work folder, which we will call WORKSPACE in this tutorial: this could be a "Code" folder in our home, a "c++" folder on our desktop, whatever you want. Create it if you don't already have, using your favourite method (mkdir in bash, or from the graphical interface in Finder). We will now define an environment variable to tell the system where our folder is. Please note down the full path of this folder, which will look like /home/$(whoami)/code/

5) Open a Terminal and type the following command (replace /full/path/to/my/folder with the previous path noted down)

```bash
echo -e "\n export WORKSPACE=/full/path/to/my/folder \n" >> ~/.bash_profile
source ~/.bash_profile
```

6) Build the project with CMake (enable or disable OMP with the define **-DOMP**:

```bash
cd $WORKSPACE
git clone https://github.com/Nico-Curti/easyDAG
cd easyDAG

mkdir -p build
cd build

cmake -DOMP=ON ..
make -j
cmake --build . --target install
cd ..
```

### Windows (7+)

1) Install Visual Studio 2017 from the [official website](https://www.visualstudio.com/)

2) Open your Powershell with Administrator privileges, type the following command and confirm it:

```PowerShell
PS \>                 Set-ExecutionPolicy unrestricted
```

3) If not already installed, please install chocolatey using the [official guide](http://chocolatey.org)

4) If you are not sure about having them updated, or even installed, please install `git`, `cmake` and an updated `Powershell`. To do so, open your Powershell with Administrator privileges and type

```PowerShell
PS \>                 cinst -y git cmake powershell
```

5) Restart the PC if required by chocolatey after the latest step

6) Install PGI 18.10 from the [official website](https://www.pgroup.com/products/community.htm) (the community edition is enough and is free; NOTE: install included MS-MPI, but avoid JRE and Cygwin)

7) Activate license for PGI 18.10 Community Edition (rename the file `%PROGRAMFILES%\PGI\license.dat-COMMUNITY-18.10` to `%PROGRAMFILES%\PGI\license.dat`) if necessary, otherwise enable a Professional License if available

8) Define a work folder, which we will call `WORKSPACE` in this tutorial: this could be a "Code" folder in our home, a "cpp" folder on our desktop, whatever you want. Create it if you don't already have, using your favourite method (mkdir in Powershell, or from the graphical interface in explorer). We will now define an environment variable to tell the system where our folder is. Please note down its full path. Open a Powershell (as a standard user) and type

```PowerShell
PS \>                 rundll32 sysdm.cpl,EditEnvironmentVariables
```

9) In the upper part of the window that pops-up, we have to create a new environment variable, with name `WORKSPACE` and value the full path noted down before.
If it not already in the `PATH` (this is possible only if you did it before), we also need to modify the "Path" variable adding the following string (on Windows 10 you need to add a new line to insert it, on Windows 7/8 it is necessary to append it using a `;` as a separator between other records):

```cmd
                      %PROGRAMFILES%\CMake\bin
```

10) If `vcpkg` is not installed, please follow the next procedure, otherwise please jump to #12

```PowerShell
PS \>                 cd $env:WORKSPACE
PS Code>              git clone https://github.com/Microsoft/vcpkg.git
PS Code>              cd vcpkg
PS Code\vcpkg>        .\bootstrap-vcpkg.bat
```

11) Open a Powershell with Administrator privileges and type

```PowerShell
PS \>                 cd $env:WORKSPACE
PS Code>              cd vcpkg
PS Code\vcpkg>        .\vcpkg integrate install
```

12) Open a Powershell and build `easyDAG` using the `build.ps1` script

```PowerShell
PS \>                 cd $env:WORKSPACE
PS Code>              git clone https://github.com/Nico-Curti/easyDAG
PS Code>              cd easyDAG
PS Code\easyDAG>      .\build.ps1
```
