# Linux Fundamentals for Embedded Systems & Robotics

## Table of Contents
1. [Why Linux for Embedded/Robotics?](#why-linux)
2. [File System Navigation](#file-system-navigation)
3. [File Operations](#file-operations)
4. [File Permissions](#file-permissions)
5. [Process Management](#process-management)
6. [System Information](#system-information)
7. [Text Processing](#text-processing)
8. [Package Management](#package-management)
9. [Networking](#networking)
10. [ROS2/Embedded Specific](#ros2-embedded-specific)

---

## Why Linux for Embedded/Robotics?

**Linux is everywhere in embedded systems and robotics:**
- ✅ Raspberry Pi, BeagleBone, NVIDIA Jetson
- ✅ ROS2 runs on Linux (Ubuntu recommended)
- ✅ Most industrial embedded systems
- ✅ Self-driving car platforms (AUTOSAR, Autoware)
- ✅ Open source, free, highly customizable

**Most used distributions:**
- Ubuntu (ROS2, general robotics)
- Raspberry Pi OS (Debian-based)
- Yocto/Buildroot (custom embedded Linux)

---

## File System Navigation

### Directory Structure
```
/           Root directory
├── /home   User home directories
├── /bin    Essential command binaries
├── /sbin   System binaries
├── /usr    User programs
├── /etc    Configuration files
├── /var    Variable data (logs)
├── /tmp    Temporary files
├── /dev    Device files (hardware)
├── /proc   Process information
└── /opt    Optional software
```

---

### Essential Navigation Commands

**pwd** - Print Working Directory
```bash
pwd
# Output: /home/username/catkin_ws
```

**ls** - List directory contents
```bash
ls              # List files
ls -l           # Long format (details)
ls -la          # Include hidden files (. files)
ls -lh          # Human-readable sizes
ls *.c          # List only .c files
```

**cd** - Change Directory
```bash
cd /home/username       # Absolute path
cd Documents           # Relative path
cd ..                  # Up one directory
cd ~                   # Home directory
cd -                   # Previous directory
```

**tree** - Display directory tree
```bash
tree                   # Show directory structure
tree -L 2              # Limit depth to 2 levels
```

---

## File Operations

### Creating Files/Directories

**touch** - Create empty file or update timestamp
```bash
touch test.txt
touch file1.c file2.c file3.c
```

**mkdir** - Make directory
```bash
mkdir project
mkdir -p path/to/deep/directory    # Create parent dirs
```

---

### Copying Files

**cp** - Copy files/directories
```bash
cp source.txt destination.txt
cp file.txt /home/user/backup/
cp -r folder/ /backup/              # Recursive (directories)
cp *.c /project/src/                # Copy all .c files
```

---

### Moving/Renaming Files

**mv** - Move or rename files
```bash
mv oldname.txt newname.txt          # Rename
mv file.txt /another/directory/     # Move
mv *.log /var/log/                  # Move all .log files
```

---

### Removing Files

**rm** - Remove files/directories
```bash
rm file.txt
rm -r directory/                    # Remove directory
rm -f file.txt                      # Force remove (no prompt)
rm -rf folder/                      # Force recursive (dangerous!)

# Never do: rm -rf /
# This deletes everything!
```

**rmdir** - Remove empty directory
```bash
rmdir empty_folder
```

---

### Viewing Files

**cat** - Display file contents
```bash
cat file.txt                        # Print entire file
cat file1.txt file2.txt             # Multiple files
```

**less** - View large files (paginated)
```bash
less large_file.log
# Navigate: Space (page down), b (page up), q (quit)
```

**head** - Show first lines
```bash
head file.txt                       # First 10 lines
head -n 20 file.txt                 # First 20 lines
```

**tail** - Show last lines
```bash
tail file.txt                       # Last 10 lines
tail -n 50 file.txt                 # Last 50 lines
tail -f /var/log/syslog             # Follow (live updates)
```

---

## File Permissions

### Understanding Permissions

```
-rwxr-xr--  1 user group 4096 Nov 10 file.txt
│││││││││
│││││││└┴─ Others: r-- (read only)
││││└┴┴─── Group:  r-x (read, execute)
│└┴┴────── Owner:  rwx (read, write, execute)
└───────── File type: - (regular file)
```

**File types:**
- `-` Regular file
- `d` Directory
- `l` Symbolic link

**Permissions:**
- `r` Read (4)
- `w` Write (2)
- `x` Execute (1)

---

### chmod - Change Permissions

**Symbolic method:**
```bash
chmod u+x script.sh                 # Add execute for user
chmod g-w file.txt                  # Remove write for group
chmod o+r file.txt                  # Add read for others
chmod a+x program                   # Add execute for all
```

**Numeric method:**
```bash
chmod 755 script.sh                 # rwxr-xr-x
chmod 644 file.txt                  # rw-r--r--
chmod 777 file.txt                  # rwxrwxrwx (dangerous!)
chmod 600 private.key               # rw------- (owner only)
```

**Common patterns:**
- `755` - Executable scripts, directories
- `644` - Regular files
- `600` - Private files (SSH keys)
- `666` - Shared files (avoid)

---

### chown - Change Ownership

```bash
sudo chown username file.txt
sudo chown username:groupname file.txt
sudo chown -R username folder/      # Recursive
```

---

## Process Management

### Viewing Processes

**ps** - Process status
```bash
ps                      # Current shell processes
ps aux                  # All processes (detailed)
ps aux | grep python    # Find Python processes
```

**top** - Real-time process viewer
```bash
top                     # Interactive, press q to quit
htop                    # Better version (install: sudo apt install htop)
```

---

### Running Processes

**Background execution:**
```bash
./long_running_program &            # Run in background
```

**Foreground/background control:**
```bash
Ctrl+Z                  # Suspend current process
bg                      # Resume in background
fg                      # Bring to foreground
jobs                    # List background jobs
```

---

### Killing Processes

**kill** - Terminate process
```bash
kill 1234               # Kill process ID 1234
kill -9 1234            # Force kill (SIGKILL)
killall python3         # Kill all python3 processes
pkill -f "ros2 run"     # Kill by pattern
```

**Common signals:**
- `15` (SIGTERM) - Graceful shutdown (default)
- `9` (SIGKILL) - Force kill
- `1` (SIGHUP) - Reload configuration

---

## System Information

**uname** - System information
```bash
uname -a                # All info
uname -r                # Kernel version
```

**df** - Disk space
```bash
df -h                   # Human-readable
```

**du** - Directory size
```bash
du -sh folder/          # Summary
du -h --max-depth=1     # One level deep
```

**free** - Memory usage
```bash
free -h                 # Human-readable
```

**lsusb** - USB devices
```bash
lsusb                   # List USB devices
```

**lspci** - PCI devices
```bash
lspci                   # List PCI devices
```

**dmesg** - Kernel messages (hardware detection)
```bash
dmesg | tail            # Recent messages
dmesg | grep -i usb     # USB related messages
```

---

## Text Processing

### grep - Search in files

```bash
grep "error" log.txt                # Find "error"
grep -i "error" log.txt             # Case-insensitive
grep -r "TODO" src/                 # Recursive search
grep -n "function" file.c           # Show line numbers
grep -v "debug" log.txt             # Invert (exclude)
```

---

### find - Find files

```bash
find . -name "*.c"                  # Find all .c files
find . -type f -name "main.c"       # Only files
find . -type d -name "build"        # Only directories
find . -mtime -7                    # Modified in last 7 days
find . -size +100M                  # Larger than 100MB
```

---

### sed - Stream editor

```bash
sed 's/old/new/' file.txt           # Replace first occurrence
sed 's/old/new/g' file.txt          # Replace all
sed -i 's/old/new/g' file.txt       # Edit in-place
```

---

### awk - Text processing

```bash
awk '{print $1}' file.txt           # Print first column
awk '{print $1, $3}' file.txt       # Print columns 1 and 3
```

---

### Piping and Redirection

**Pipe (|)** - Send output to another command
```bash
ls -l | grep ".txt"                 # Find .txt files
cat file.txt | wc -l                # Count lines
ps aux | grep python                # Find python processes
```

**Redirection:**
```bash
ls > output.txt                     # Overwrite file
ls >> output.txt                    # Append to file
./program 2> error.log              # Redirect errors
./program &> all.log                # Redirect all output
```

---

## Package Management

### apt (Ubuntu/Debian)

**Update package list:**
```bash
sudo apt update
```

**Upgrade packages:**
```bash
sudo apt upgrade
```

**Install package:**
```bash
sudo apt install python3-pip
sudo apt install ros-humble-desktop
```

**Remove package:**
```bash
sudo apt remove package_name
sudo apt autoremove                 # Remove unused dependencies
```

**Search packages:**
```bash
apt search robot
```

---

## Networking

### ifconfig / ip - Network configuration

```bash
ifconfig                            # Show network interfaces
ip addr show                        # Modern alternative
ip link show                        # Show link status
```

---

### ping - Test connectivity

```bash
ping google.com
ping -c 4 192.168.1.1               # Send 4 packets
```

---

### SSH - Remote access

```bash
ssh username@192.168.1.100
ssh -p 2222 user@server             # Custom port
scp file.txt user@server:/path/     # Copy file to remote
```

---

### netstat / ss - Network connections

```bash
netstat -tuln                       # Show listening ports
ss -tuln                            # Modern alternative
```

---

## ROS2/Embedded Specific Commands

### Device Files

**List serial devices:**
```bash
ls -l /dev/tty*                     # All serial devices
ls -l /dev/ttyUSB*                  # USB serial
ls -l /dev/ttyACM*                  # Arduino/CDC devices
```

**Check device permissions:**
```bash
ls -l /dev/ttyUSB0
# If no access: sudo usermod -a -G dialout $USER
# Then logout and login
```

---

### ROS2 Workspace Commands

**Build workspace:**
```bash
cd ~/ros2_ws
colcon build
colcon build --packages-select my_package
```

**Source workspace:**
```bash
source /opt/ros/humble/setup.bash   # ROS2 installation
source ~/ros2_ws/install/setup.bash # Your workspace
```

**List topics:**
```bash
ros2 topic list
ros2 topic echo /cmd_vel
ros2 topic hz /scan
```

**Run nodes:**
```bash
ros2 run package_name node_name
ros2 launch package_name launch_file.py
```

---

### Git Commands (Essential)

```bash
git clone https://github.com/user/repo.git
git status
git add .
git commit -m "message"
git push
git pull
git log
```

---

### Bashrc Configuration

**Edit bashrc:**
```bash
nano ~/.bashrc
```

**Common additions for ROS2:**
```bash
# Add to ~/.bashrc
source /opt/ros/humble/setup.bash
source ~/ros2_ws/install/setup.bash
export ROS_DOMAIN_ID=0
alias ros2_build='cd ~/ros2_ws && colcon build && source install/setup.bash'
```

**Reload bashrc:**
```bash
source ~/.bashrc
```

---

## Essential Shortcuts

**Terminal shortcuts:**
```
Ctrl+C          Kill current process
Ctrl+Z          Suspend current process
Ctrl+D          Exit shell / End of file
Ctrl+L          Clear screen
Ctrl+R          Search command history
Ctrl+A          Move to line start
Ctrl+E          Move to line end
Tab             Auto-complete
↑/↓             Command history
```

---

## Common Tasks Quick Reference

### Find ROS2 packages
```bash
ros2 pkg list | grep navigation
```

### Check CPU temperature (Raspberry Pi)
```bash
vcgencmd measure_temp
```

### Monitor serial port
```bash
sudo apt install screen
screen /dev/ttyUSB0 115200          # Exit: Ctrl+A then K
```

### Check disk usage
```bash
df -h
du -sh *
```

### Find large files
```bash
find . -type f -size +100M -exec ls -lh {} \;
```

### System logs
```bash
tail -f /var/log/syslog             # Live system log
journalctl -f                       # Systemd journal
```

### Archive and compress
```bash
tar -czvf archive.tar.gz folder/    # Create archive
tar -xzvf archive.tar.gz            # Extract archive
```

---

## Interview Questions

**Q: "How to find all .c files in current directory?"**
```bash
find . -name "*.c"
# or
ls *.c
```

**Q: "How to check if serial device is available?"**
```bash
ls -l /dev/ttyUSB0
dmesg | grep tty
```

**Q: "How to make script executable?"**
```bash
chmod +x script.sh
# or
chmod 755 script.sh
```

**Q: "How to find process using specific port?"**
```bash
sudo netstat -tuln | grep 8080
# or
sudo ss -tuln | grep 8080
```

**Q: "How to redirect both stdout and stderr?"**
```bash
./program &> output.log
# or
./program > output.log 2>&1
```

**Q: "Difference between soft and hard link?"**
- Hard link: Same inode, same file. Delete original, link remains
- Soft link (symlink): Pointer to file. Delete original, link breaks
```bash
ln original.txt hard_link.txt       # Hard link
ln -s original.txt soft_link.txt    # Soft link
```

---

## Best Practices

1. **Always use `sudo` carefully** - Double check before running
2. **Never `rm -rf /`** - Deletes everything
3. **Use tab completion** - Saves time and prevents typos
4. **Check device permissions** - Add user to dialout group for serial
5. **Source ROS2 workspace** - Always source after build
6. **Use version control** - Git for all projects
7. **Read man pages** - `man command` for detailed help
8. **Test commands first** - Use `echo` before destructive operations

---

## Quick Command Cheat Sheet

```bash
# Navigation
pwd                     # Print working directory
ls -la                  # List all files
cd path                 # Change directory

# File Operations
cp src dst              # Copy
mv src dst              # Move/rename
rm file                 # Remove
mkdir dir               # Make directory

# Viewing
cat file                # Display file
less file               # Paginated view
head file               # First lines
tail -f file            # Follow file

# Permissions
chmod 755 file          # Change permissions
chown user file         # Change owner

# Process
ps aux                  # List processes
top                     # Monitor processes
kill PID                # Kill process
killall name            # Kill by name

# Search
grep pattern file       # Search in file
find . -name "*.c"      # Find files

# System
df -h                   # Disk space
free -h                 # Memory usage
uname -a                # System info

# Network
ifconfig                # Network interfaces
ping host               # Test connectivity
ssh user@host           # Remote login

# Package
sudo apt update         # Update package list
sudo apt install pkg    # Install package

# ROS2
ros2 topic list         # List topics
ros2 run pkg node       # Run node
colcon build            # Build workspace
```

---

**Master these Linux fundamentals and you'll be productive in embedded systems and robotics development! 🐧🚀**

**For ROS2 development, Ubuntu 22.04 with ROS2 Humble is recommended.**
