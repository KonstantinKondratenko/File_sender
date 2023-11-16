# File_sender
На чистую виртуальную машину Ubuntu необходимо установить:
Github
Anaconda
gym-pybullet-drones

1) Установка  Git: sudo apt install git

2) Установка Anaconda:
cd /tmp
curl https://repo.anaconda.com/archive/Anaconda3-2023.09-0-Linux-x86_64.sh --output anaconda.sh
bash anaconda.sh – и отвечаем “Yes”  на вопросы скрипта
source ~/.bashrc
conda list - проверяем, что анаконда поставилась

3) Установка cd gym-pybullet-drones: 
git clone https://github.com/utiasDSL/gym-pybullet-drones.git
cd gym-pybullet-drones/ 
conda create -n drones python=3.10
conda activate drones
pip3 install --upgrade pip
pip3 install -e . 

