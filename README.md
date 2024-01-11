clone the crow repository 
git clone --recursive https://github.com/ipkn/crow

cd crow
sudo apt-get update
sudo apt-get install -y cmake g++ make

mkdir build
cd build

create a soft link btn python and python3
sudo ln -s /usr/bin/python3 /usr/bin/python

boost librry not 1.70+ it would have compatibility issues

for manual installation download tar files from the following link
https://www.boost.org/users/history/version_1_64_0.html

then untar , run ./bootstrap.sh then ./b2

cmake ..
make


check if /usr/local/lib is included in system path by the following commnad:
echo $LD_LIBRARY_PATH
if not 
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

update dynamic linker cache by the following command
sudo ldconfig
