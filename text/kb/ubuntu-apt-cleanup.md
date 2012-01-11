Cleaning up an APT-based Debian/Ubuntu system
---------------------------------------------

### Where is my space?
    df -H
    du -sm ~
    find ~ -type f -size +100M -print0 | xargs -0 ls -l
    sudo apt-cache search baobab

### Log archives
    sudo ls -l /var/log
    rm /var/log/*.{1,2,3,4}
    rm /var/log/*.gz

### Update your system
    sudo apt-get update && sudo apt-get dist-upgrade -y

### Bring the *APT* system to the consistent state
    sudo apt-get -f install

### Save your packages selection 
    sudo dpkg --get-selections '*' | vim -

### Use Synaptic package manager
*Synaptic* > _Installed_, _Installed(local)_ > review and mark to remove unused > *Apply*.

### apt-get autoclean
    sudo ls /var/cache/apt/archives/
    sudo ls /var/cache/apt/archives/partial/
    sudo apt-get autoclean
    sudo apt-get clean
    sudo rm /var/cache/apt/archives/partial/*

### deborphan
    sudo apt-get install deborphan
    sudo deborphan
    sudo deborphan | xargs sudo apt-get -y remove --purge

### Jiu Jitsu hardcore
    sudo apt-get install debfoster
    man debfoster
    sudo debfoster -q
    sudo debfoster

### More Jiu Jitsu hardcore
    sudo apt-get install wajig
    sudo gjig

[See also commandlinefu.com](http://www.commandlinefu.com/)

[okertanov@gmail.com](mailto:okertanov@gmail.com)