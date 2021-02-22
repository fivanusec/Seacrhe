make
sudo cp Searche /usr/bin/
if [ $? -eq 0 ]; then
        echo Searche installed successfully
else
        echo I see you have it already
        sudo rm /usr/bin/Searche
        sudo cp Searche /usr/bin
	echo Searche updated!
fi
