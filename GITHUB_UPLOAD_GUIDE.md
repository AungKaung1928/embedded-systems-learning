# How to Upload to GitHub from Ubuntu Terminal
## Complete Beginner's Guide

---

## PART 1: PREREQUISITES (5 minutes)

### Step 1A: Check if Git is installed
```bash
git --version
```
**Expected output:** `git version 2.43.0` (or similar)

If NOT installed, run:
```bash
sudo apt update
sudo apt install git
```

### Step 1B: Configure Git (one-time setup)
```bash
git config --global user.name "Your Name"
git config --global user.email "your.email@gmail.com"
```

**Example:**
```bash
git config --global user.name "John Doe"
git config --global user.email "john.doe@gmail.com"
```

**Verify it worked:**
```bash
git config --global user.name
git config --global user.email
```

---

## PART 2: CREATE REPOSITORY ON GITHUB (5 minutes)

### Step 2A: Go to GitHub and create a new repository

1. Open browser and go to: **https://github.com**
2. Log in to your account (create one if needed - it's free!)
3. Click the **"+"** icon in top-right corner
4. Select **"New repository"**

### Step 2B: Fill in repository details

**Repository name:** (choose one)
- `embedded-systems-learning`
- `c-embedded-drone`
- `liberaware-learning`
- Pick any name you like!

**Description:** (optional but good to add)
- `C programming fundamentals for embedded systems engineering and autonomous drone development`

**Visibility:** Choose one:
- **Public** = Anyone can see it (good for learning/portfolio)
- **Private** = Only you can see it (good if you want privacy)

**Recommended for portfolio:** Choose **Public**

### Step 2C: Initialize repository

✓ Check the box: **"Add a README file"**
✓ Select .gitignore: **"C"**
✓ License: (skip for now)

Click **"Create repository"**

### Step 2D: Get the repository URL

After creation, you'll see a green button **"< > Code"**

Click it and copy the HTTPS URL:
```
https://github.com/YOUR-USERNAME/embedded-systems-learning.git
```

**Save this URL somewhere!** You'll need it in Part 3.

---

## PART 3: DOWNLOAD FILES TO YOUR COMPUTER (5 minutes)

### Step 3A: Create a folder for your project
```bash
mkdir my-embedded-project
cd my-embedded-project
```

### Step 3B: Download the learning files

Option 1: If you already have the files
```bash
# Files are already in: /mnt/user-data/outputs/
# Copy them to your project folder:
cp /mnt/user-data/outputs/*.c .
cp /mnt/user-data/outputs/*.txt .
cp /mnt/user-data/outputs/*.md .
```

Option 2: If you need to create them fresh
```bash
# Just continue - we'll create all files in the next step
```

### Step 3C: Verify files are there
```bash
ls -la
```

You should see:
```
01_hello_embedded.c
02_pointers_arrays.c
03_structs_bitfields.c
04_practical_tasks.c
05_functions_modularity.c
CHEAT_SHEET.txt
C_EMBEDDED_GUIDE.txt
PACKAGE_OVERVIEW.txt
README.txt
```

---

## PART 4: INITIALIZE GIT REPOSITORY (2 minutes)

### Step 4A: Go to your project folder
```bash
cd my-embedded-project
```

### Step 4B: Initialize Git
```bash
git init
```

**Output:** `Initialized empty Git repository in /home/username/my-embedded-project/.git/`

### Step 4C: Add all files to Git
```bash
git add .
```

This tells Git: "Track all these files"

### Step 4D: Create first commit (save point)
```bash
git commit -m "Initial commit: Add C embedded systems learning materials"
```

**What this does:**
- Creates a snapshot of your files
- The `-m` flag adds a message describing what you did

**Expected output:**
```
[main (root-commit) abc1234] Initial commit: Add C embedded systems materials
 9 files changed, 15000 insertions(+)
 create mode 100644 01_hello_embedded.c
 ...
```

---

## PART 5: CONNECT TO GITHUB (2 minutes)

### Step 5A: Add the remote repository

Replace `YOUR-USERNAME` with your actual GitHub username:

```bash
git remote add origin https://github.com/YOUR-USERNAME/embedded-systems-learning.git
```

**Example:**
```bash
git remote add origin https://github.com/john-doe-123/embedded-systems-learning.git
```

### Step 5B: Verify connection
```bash
git remote -v
```

**Expected output:**
```
origin  https://github.com/YOUR-USERNAME/embedded-systems-learning.git (fetch)
origin  https://github.com/YOUR-USERNAME/embedded-systems-learning.git (push)
```

---

## PART 6: UPLOAD TO GITHUB (2 minutes)

### Step 6A: Push to GitHub

```bash
git branch -M main
git push -u origin main
```

**What this does:**
- Renames your branch to `main` (GitHub standard)
- `-u` flag sets this as your default branch
- Uploads all your files to GitHub!

### Step 6B: Enter GitHub credentials (if prompted)

GitHub might ask for authentication. You have two options:

**Option 1: Personal Access Token (RECOMMENDED)**

1. Go to: https://github.com/settings/tokens
2. Click "Generate new token" → "Generate new token (classic)"
3. Give it a name: `Git Ubuntu`
4. Select scopes: Check ☑️ `repo`
5. Click "Generate token"
6. **Copy the token** (it shows once!)
7. Paste it when asked for password

**Option 2: SSH Key (Advanced - skip for now)**

---

## PART 7: VERIFY UPLOAD SUCCESS (1 minute)

### Step 7A: Check on GitHub website

1. Go to: `https://github.com/YOUR-USERNAME/embedded-systems-learning`
2. You should see all your files listed!
3. Click on each file to preview the content

### Step 7B: Verify from terminal
```bash
git log
```

**Expected output:**
```
commit abc1234567... (HEAD -> main, origin/main)
Author: Your Name <your.email@gmail.com>
Date:   Sat Oct 24 12:00:00 2025 +0000

    Initial commit: Add C embedded systems learning materials
```

---

## COMPLETE WORKFLOW (All Steps Together)

Here's the entire process as one continuous command sequence:

```bash
# 1. Configure Git (one time only)
git config --global user.name "Your Name"
git config --global user.email "your.email@gmail.com"

# 2. Create project folder
mkdir my-embedded-project
cd my-embedded-project

# 3. Copy files (if you have them already)
cp /mnt/user-data/outputs/*.c .
cp /mnt/user-data/outputs/*.txt .
cp /mnt/user-data/outputs/*.md .

# 4. Initialize Git
git init
git add .
git commit -m "Initial commit: Add C embedded systems learning materials"

# 5. Connect to GitHub (replace YOUR-USERNAME)
git remote add origin https://github.com/YOUR-USERNAME/embedded-systems-learning.git
git branch -M main

# 6. Upload to GitHub
git push -u origin main

# 7. Verify
git log
```

---

## WHAT FILES SHOULD YOU UPLOAD?

### **YES - Upload These Files:**

✅ **C Program Files:**
- `01_hello_embedded.c`
- `02_pointers_arrays.c`
- `03_structs_bitfields.c`
- `04_practical_tasks.c`
- `05_functions_modularity.c`

✅ **Documentation:**
- `README.txt` (main guide)
- `C_EMBEDDED_GUIDE.txt` (learning concepts)
- `CHEAT_SHEET.txt` (quick reference)
- `PACKAGE_OVERVIEW.txt` (visual overview)
- `GITHUB_UPLOAD_GUIDE.md` (this file!)

✅ **Additional Files (create these):**
- `.gitignore` (tells Git what to ignore)
- Compiled programs (optional)

### **NO - Don't Upload These:**
- Compiled executables (01_hello_embedded, etc.)
- Object files (.o files)
- Large binary files
- Your personal information

---

## HOW TO ORGANIZE YOUR REPOSITORY

Recommended folder structure:

```
embedded-systems-learning/
├── README.md                    (main project description)
├── CHEAT_SHEET.txt             (quick reference)
├── C_EMBEDDED_GUIDE.txt        (learning materials)
├── PACKAGE_OVERVIEW.txt        (visual guide)
│
├── C_Programs/
│   ├── 01_hello_embedded.c
│   ├── 02_pointers_arrays.c
│   ├── 03_structs_bitfields.c
│   ├── 04_practical_tasks.c
│   └── 05_functions_modularity.c
│
├── Documentation/
│   ├── GITHUB_UPLOAD_GUIDE.md
│   └── Learning_Path.txt
│
├── .gitignore
└── .git/                        (hidden - created automatically)
```

To organize this way:

```bash
mkdir C_Programs
mkdir Documentation
mv *.c C_Programs/
mv C_EMBEDDED_GUIDE.txt Documentation/
git add .
git commit -m "Organize files into folders"
git push
```

---

## UPDATING YOUR REPOSITORY (Adding New Files)

Once you've created your repository, updating is easy:

```bash
# 1. Go to your project folder
cd my-embedded-project

# 2. Make changes (add new files, modify files, etc.)
# ... do your work ...

# 3. Add changes
git add .

# 4. Create a commit (save point)
git commit -m "Add new practice program: temperature logger"

# 5. Upload to GitHub
git push
```

---

## USEFUL GIT COMMANDS

```bash
# See status of your files
git status

# See history of commits
git log

# See what changed in last commit
git diff HEAD~1

# Undo changes to a file
git checkout -- filename.c

# See all branches
git branch -a

# Create a new branch (for experiments)
git checkout -b feature/new-feature

# Switch to main branch
git checkout main
```

---

## TROUBLESHOOTING

### Problem: "fatal: not a git repository"
**Solution:** Make sure you're in the correct folder with `.git` subfolder
```bash
pwd                    # Check current location
ls -la                 # Should show .git folder
```

### Problem: "Please tell me who you are"
**Solution:** Configure Git
```bash
git config --global user.name "Your Name"
git config --global user.email "your.email@gmail.com"
```

### Problem: "Permission denied (publickey)"
**Solution:** Use HTTPS instead of SSH, or generate SSH key
```bash
git remote set-url origin https://github.com/USERNAME/repo.git
```

### Problem: "fatal: remote origin already exists"
**Solution:** Your remote is already configured, just push
```bash
git push -u origin main
```

### Problem: Files won't upload / "Nothing to commit"
**Solution:** Make sure you added files
```bash
git add .              # Add all files
git status            # Check what's staged
git commit -m "message"
git push
```

---

## BEST PRACTICES

1. **Commit often** - Make commits after each meaningful change
2. **Write good commit messages** - Describe what you changed
3. **Use .gitignore** - Ignore compiled files and temporary files
4. **Pull before push** - If working with others
5. **Keep it organized** - Use folders and good file names

---

## NEXT STEPS AFTER UPLOADING

1. ✅ Your files are now on GitHub!
2. Create a nice README.md to explain your project
3. Add your GitHub link to your resume/portfolio
4. Continue adding more programs as you learn
5. Create branches for experimentation
6. Star other embedded systems projects for learning

---

## EXAMPLE COMMIT MESSAGES

Good examples:
```
git commit -m "Add ADC sensor conversion function"
git commit -m "Fix pointer arithmetic in sensor reading loop"
git commit -m "Add low-pass filter implementation"
git commit -m "Organize code into C_Programs folder"
```

Bad examples:
```
git commit -m "update"
git commit -m "blah"
git commit -m "xxx"
```

---

## YOU'RE READY!

You now have everything you need to:
1. ✅ Create a GitHub repository
2. ✅ Upload your embedded systems learning materials
3. ✅ Update it as you learn
4. ✅ Share it with others and build your portfolio

**Your GitHub repository will serve as:**
- 📚 Your learning journal
- 💼 A portfolio project
- 🚀 A resource for others learning embedded systems
- 📊 Evidence of your learning journey

Good luck! 🎉

---

## QUICK REFERENCE CARD

```
SETUP (one time):
git config --global user.name "Your Name"
git config --global user.email "email@gmail.com"

CREATE NEW REPO:
mkdir project_name
cd project_name
git init
git add .
git commit -m "Initial commit"
git remote add origin https://github.com/USERNAME/project.git
git branch -M main
git push -u origin main

UPDATE EXISTING REPO:
git add .
git commit -m "Your message"
git push

CHECK STATUS:
git status
git log
```

