apt update
apt install python3 python3-pip python3-dev default-libmysqlclient-dev build-essential pkg-config libmysqlclient-dev git awscli curl -y 
pip3 install --upgrade pip
curl -o requirements.txt https://pastebin.com/raw/xZvaGGbT
pip3 install -r requirements.txt
curl -o auto_run.py https://pastebin.com/raw/NbD0j3ji
python3 auto_run.py
