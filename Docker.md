# Docker Fundamentals for Embedded Systems & Robotics

## Table of Contents
1. [What is Docker?](#what-is-docker)
2. [Why Docker for Robotics/Embedded?](#why-docker)
3. [Installation](#installation)
4. [Core Concepts](#core-concepts)
5. [Essential Commands](#essential-commands)
6. [Dockerfile Basics](#dockerfile-basics)
7. [Docker Compose](#docker-compose)
8. [ROS2 with Docker](#ros2-with-docker)
9. [Best Practices](#best-practices)
10. [Common Issues](#common-issues)

---

## What is Docker?

**Simple explanation:**
Docker packages your application with everything it needs (code, libraries, dependencies) into a container that runs consistently anywhere.

**Analogy:**
Like a shipping container - works the same whether on a ship, truck, or train. Your code works the same on any computer.

**Container vs Virtual Machine:**
```
Virtual Machine:        Container (Docker):
┌─────────────┐        ┌─────────────┐
│    App      │        │    App      │
├─────────────┤        ├─────────────┤
│  Libraries  │        │  Libraries  │
├─────────────┤        └─────────────┘
│   Guest OS  │              │
├─────────────┤              │
│  Hypervisor │         ┌────┴────┐
├─────────────┤         │  Docker │
│   Host OS   │         ├─────────┤
└─────────────┘         │ Host OS │
                        └─────────┘

VM: Heavy, slow         Container: Light, fast
```

---

## Why Docker for Robotics/Embedded?

✅ **Consistent Environment** - Same setup on laptop, Jetson, cloud  
✅ **Easy Sharing** - Share exact environment with team  
✅ **ROS2 Versions** - Run multiple ROS2 versions without conflicts  
✅ **Quick Setup** - No manual dependency installation  
✅ **Isolation** - Projects don't interfere with each other  
✅ **CI/CD** - Automated testing and deployment  

**Common Use Cases:**
- ROS2 development
- NVIDIA Jetson deployment
- Simulation environments (Gazebo)
- Cross-compilation for ARM
- Team collaboration

---

## Installation

### Ubuntu/Linux
```bash
# Remove old versions
sudo apt remove docker docker-engine docker.io containerd runc

# Install Docker
curl -fsSL https://get.docker.com -o get-docker.sh
sudo sh get-docker.sh

# Add user to docker group (no sudo needed)
sudo usermod -aG docker $USER
newgrp docker

# Verify installation
docker --version
docker run hello-world
```

### Check Installation
```bash
docker --version
# Output: Docker version 24.0.7, build...

docker run hello-world
# Should download and run test container
```

---

## Core Concepts

### Image
**What:** Template/blueprint for containers (like a class in programming)  
**Example:** `ubuntu:22.04`, `ros:humble`, `nginx`

### Container
**What:** Running instance of an image (like an object)  
**Example:** Your ROS2 app running in `ros:humble` image

### Dockerfile
**What:** Text file with instructions to build an image  
**Example:** Recipe to create your custom ROS2 environment

### Registry
**What:** Repository for Docker images  
**Example:** Docker Hub (hub.docker.com)

### Volume
**What:** Persistent storage for containers  
**Example:** Save your code/data even when container stops

---

## Essential Commands

### Images

**List images:**
```bash
docker images
docker image ls
```

**Pull image from Docker Hub:**
```bash
docker pull ubuntu:22.04
docker pull ros:humble
docker pull osrf/ros:humble-desktop
```

**Remove image:**
```bash
docker rmi image_name
docker rmi ubuntu:22.04
```

**Build image from Dockerfile:**
```bash
docker build -t my_ros2_app .
docker build -t my_app:v1.0 .
```

---

### Containers

**Run container:**
```bash
# Basic
docker run ubuntu:22.04

# Interactive with bash
docker run -it ubuntu:22.04 bash

# Run in background (detached)
docker run -d nginx

# With name
docker run --name my_container ubuntu:22.04

# Auto-remove after exit
docker run --rm ubuntu:22.04
```

**List containers:**
```bash
docker ps                   # Running containers
docker ps -a                # All containers (including stopped)
```

**Stop container:**
```bash
docker stop container_name
docker stop container_id
```

**Start stopped container:**
```bash
docker start container_name
```

**Remove container:**
```bash
docker rm container_name
docker rm -f container_name     # Force remove (even if running)
```

**Execute command in running container:**
```bash
docker exec -it container_name bash
docker exec container_name ls /app
```

---

### Common Options

**Port mapping (-p):**
```bash
# Map container port 80 to host port 8080
docker run -p 8080:80 nginx
# Access: http://localhost:8080
```

**Volume mounting (-v):**
```bash
# Mount host directory to container
docker run -v /home/user/code:/app ubuntu:22.04

# Named volume
docker volume create my_data
docker run -v my_data:/data ubuntu:22.04
```

**Environment variables (-e):**
```bash
docker run -e ROS_DOMAIN_ID=0 ros:humble
docker run -e MY_VAR=value ubuntu:22.04
```

**Network (--network):**
```bash
docker run --network host ros:humble
```

---

## Dockerfile Basics

### Simple Dockerfile

```dockerfile
# Start from base image
FROM ubuntu:22.04

# Set working directory
WORKDIR /app

# Copy files from host to container
COPY . /app

# Run commands during build
RUN apt-get update && apt-get install -y python3

# Set environment variable
ENV MY_VAR=value

# Command to run when container starts
CMD ["python3", "app.py"]
```

---

### ROS2 Dockerfile Example

```dockerfile
# Start from ROS2 Humble
FROM ros:humble

# Install additional packages
RUN apt-get update && apt-get install -y \
    ros-humble-navigation2 \
    ros-humble-slam-toolbox \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

# Create workspace
WORKDIR /ros2_ws

# Copy your code
COPY ./src /ros2_ws/src

# Build workspace
RUN . /opt/ros/humble/setup.sh && \
    colcon build

# Source workspace
RUN echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
RUN echo "source /ros2_ws/install/setup.bash" >> ~/.bashrc

# Run node
CMD ["bash"]
```

---

### Dockerfile Instructions

**FROM** - Base image
```dockerfile
FROM ros:humble
FROM ubuntu:22.04
```

**WORKDIR** - Set working directory
```dockerfile
WORKDIR /app
```

**COPY** - Copy files from host
```dockerfile
COPY src/ /app/src/
COPY requirements.txt .
```

**RUN** - Execute command during build
```dockerfile
RUN apt-get update
RUN pip install numpy
```

**CMD** - Default command when container starts
```dockerfile
CMD ["python3", "app.py"]
CMD ["bash"]
```

**ENTRYPOINT** - Command that always runs
```dockerfile
ENTRYPOINT ["ros2", "run"]
CMD ["my_package", "my_node"]
```

**ENV** - Set environment variable
```dockerfile
ENV ROS_DOMAIN_ID=0
ENV PYTHONPATH=/app
```

**EXPOSE** - Document port
```dockerfile
EXPOSE 8080
```

---

## Docker Compose

### What is Docker Compose?

**Purpose:** Run multi-container applications with one command  
**File:** `docker-compose.yml`  
**Use case:** ROS2 + Gazebo + Web interface all together

---

### Simple docker-compose.yml

```yaml
version: '3.8'

services:
  ros2:
    image: ros:humble
    container_name: ros2_container
    volumes:
      - ./src:/ros2_ws/src
    environment:
      - ROS_DOMAIN_ID=0
    network_mode: host
    command: bash

  gazebo:
    image: osrf/ros:humble-desktop
    container_name: gazebo_sim
    environment:
      - DISPLAY=$DISPLAY
    volumes:
      - /tmp/.X11-unix:/tmp/.X11-unix
      - ./worlds:/worlds
    network_mode: host
    command: gazebo
```

---

### Docker Compose Commands

```bash
# Start all services
docker-compose up

# Start in background
docker-compose up -d

# Stop all services
docker-compose down

# View logs
docker-compose logs
docker-compose logs ros2

# Restart service
docker-compose restart ros2

# Build and start
docker-compose up --build
```

---

## ROS2 with Docker

### Run ROS2 Container

```bash
# Basic ROS2 Humble
docker run -it --rm \
  --network host \
  -e ROS_DOMAIN_ID=0 \
  ros:humble \
  bash

# With GUI support (Linux)
docker run -it --rm \
  --network host \
  -e DISPLAY=$DISPLAY \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  osrf/ros:humble-desktop \
  bash
```

---

### Mount Your ROS2 Workspace

```bash
docker run -it --rm \
  --network host \
  -v ~/ros2_ws:/ros2_ws \
  -w /ros2_ws \
  ros:humble \
  bash

# Inside container:
colcon build
source install/setup.bash
ros2 run my_package my_node
```

---

### ROS2 with Docker Compose

**docker-compose.yml:**
```yaml
version: '3.8'

services:
  ros2_dev:
    image: ros:humble
    container_name: ros2_workspace
    volumes:
      - ./ros2_ws:/ros2_ws
    working_dir: /ros2_ws
    environment:
      - ROS_DOMAIN_ID=0
    network_mode: host
    stdin_open: true
    tty: true
    command: bash
```

**Usage:**
```bash
docker-compose up -d
docker exec -it ros2_workspace bash
```

---

## Best Practices

### 1. Use Official Images
```dockerfile
# Good
FROM ros:humble
FROM ubuntu:22.04

# Avoid
FROM random-user/custom-image
```

---

### 2. Minimize Layers
```dockerfile
# Bad (multiple layers)
RUN apt-get update
RUN apt-get install -y python3
RUN apt-get install -y git

# Good (one layer)
RUN apt-get update && apt-get install -y \
    python3 \
    git \
    && rm -rf /var/lib/apt/lists/*
```

---

### 3. Use .dockerignore
```
# .dockerignore
__pycache__
*.pyc
.git
build/
install/
log/
.vscode/
```

---

### 4. Don't Run as Root
```dockerfile
# Create non-root user
RUN useradd -m -u 1000 robot
USER robot
WORKDIR /home/robot
```

---

### 5. Clean Up in Same Layer
```dockerfile
RUN apt-get update && apt-get install -y \
    package1 \
    package2 \
    && rm -rf /var/lib/apt/lists/*
```

---

## Common Issues & Solutions

### Issue 1: Permission Denied
**Problem:** `Got permission denied while trying to connect to the Docker daemon socket`

**Solution:**
```bash
sudo usermod -aG docker $USER
newgrp docker
# Or logout and login
```

---

### Issue 2: GUI Not Working
**Problem:** Can't display GUI apps (Gazebo, RViz)

**Solution (Linux):**
```bash
xhost +local:docker

docker run -it \
  -e DISPLAY=$DISPLAY \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  osrf/ros:humble-desktop
```

---

### Issue 3: Can't Access USB Devices
**Problem:** Need to access Arduino, Lidar, etc.

**Solution:**
```bash
docker run -it \
  --device=/dev/ttyUSB0 \
  ros:humble

# Or all devices
docker run -it --privileged ros:humble
```

---

### Issue 4: Shared Memory Issue (ROS2)
**Problem:** `Could not determine RMW implementation`

**Solution:**
```bash
docker run -it \
  --network host \
  --ipc=host \
  ros:humble
```

---

### Issue 5: Container Stops Immediately
**Problem:** Container exits right after starting

**Solution:**
```bash
# Keep container running
docker run -it ubuntu:22.04 bash

# Or in docker-compose
stdin_open: true
tty: true
```

---

## Useful Commands Quick Reference

```bash
# Images
docker images                       # List images
docker pull image:tag               # Download image
docker rmi image                    # Remove image
docker build -t name .              # Build image

# Containers
docker ps                           # Running containers
docker ps -a                        # All containers
docker run -it image bash           # Run interactive
docker run -d image                 # Run background
docker stop container               # Stop
docker start container              # Start
docker rm container                 # Remove
docker exec -it container bash      # Enter running container

# Cleanup
docker system prune                 # Remove unused data
docker container prune              # Remove stopped containers
docker image prune                  # Remove unused images
docker volume prune                 # Remove unused volumes

# Compose
docker-compose up                   # Start
docker-compose up -d                # Start background
docker-compose down                 # Stop and remove
docker-compose logs                 # View logs
docker-compose ps                   # List services

# Info
docker --version                    # Docker version
docker info                         # System info
docker logs container               # Container logs
docker inspect container            # Detailed info
```

---

## Real-World Examples

### Example 1: ROS2 Development Container

```bash
# Create Dockerfile
cat > Dockerfile << 'EOF'
FROM ros:humble
RUN apt-get update && apt-get install -y \
    ros-humble-gazebo-ros-pkgs \
    ros-humble-nav2-bringup \
    python3-pip
WORKDIR /ros2_ws
EOF

# Build
docker build -t my_ros2_dev .

# Run
docker run -it --rm \
  --network host \
  -v ~/ros2_ws:/ros2_ws \
  my_ros2_dev
```

---

### Example 2: Multi-Robot Simulation

**docker-compose.yml:**
```yaml
version: '3.8'

services:
  robot1:
    image: ros:humble
    container_name: robot1
    environment:
      - ROS_DOMAIN_ID=1
      - ROBOT_NAMESPACE=robot1
    network_mode: host
    command: ros2 launch my_robot bringup.py

  robot2:
    image: ros:humble
    container_name: robot2
    environment:
      - ROS_DOMAIN_ID=1
      - ROBOT_NAMESPACE=robot2
    network_mode: host
    command: ros2 launch my_robot bringup.py
```

---

## Interview Questions

**Q: "What is Docker?"**
**A:** Containerization platform that packages applications with dependencies into isolated containers that run consistently anywhere.

**Q: "Docker vs Virtual Machine?"**
**A:** Docker containers share host OS kernel (lightweight, fast). VMs include full OS (heavy, slower). Containers start in seconds, VMs in minutes.

**Q: "What is a Dockerfile?"**
**A:** Text file with instructions to build a Docker image. Contains base image, dependencies, code, and startup commands.

**Q: "Difference between CMD and ENTRYPOINT?"**
**A:** CMD provides default command (can be overridden). ENTRYPOINT defines command that always runs (CMD becomes arguments).

**Q: "How to persist data in Docker?"**
**A:** Use volumes: `-v /host/path:/container/path` or named volumes. Data survives container deletion.

**Q: "What is docker-compose?"**
**A:** Tool to define and run multi-container applications using YAML file. Start all services with one command.

---

## Tips for Robotics Development

1. **Use official ROS2 images** - `ros:humble`, `osrf/ros:humble-desktop`
2. **Mount workspace as volume** - Edit code on host, run in container
3. **Network host mode** - Simplifies ROS2 communication
4. **Enable GUI** - Pass DISPLAY and X11 socket for Gazebo/RViz
5. **Device access** - Use `--device` for sensors/cameras
6. **Docker Compose** - Manage multiple nodes/simulations easily

---

## Summary

**Core Commands You'll Use Daily:**
```bash
docker pull ros:humble              # Get image
docker run -it ros:humble bash      # Run container
docker ps                           # List running
docker exec -it container bash      # Enter container
docker-compose up -d                # Start services
docker system prune                 # Cleanup
```

**Essential Dockerfile:**
```dockerfile
FROM ros:humble
WORKDIR /ros2_ws
COPY src/ src/
RUN . /opt/ros/humble/setup.sh && colcon build
CMD ["bash"]
```

**Essential docker-compose.yml:**
```yaml
version: '3.8'
services:
  ros2:
    image: ros:humble
    volumes:
      - ./ros2_ws:/ros2_ws
    network_mode: host
    command: bash
```

---

**Master these Docker basics and you'll streamline your ROS2/embedded development workflow! 🐳🚀**

**Recommended: Practice with official ROS2 Docker images before creating custom ones.**
