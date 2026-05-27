# UY1 Learning Management System (C-LMS)

A console-based learning management platform built in C, developed as part of the
end-of-semester project for Licence 1 Informatique at the University of Yaoundé 1.

## Academic Context

**Course:** Licence 1 Informatique
**Institution:** Université de Yaoundé 1
**Semester:** Semestre 2, 2026
**Module:** INF132 — Programmation en C

---

## 📌 Read This First

If you just joined this project, read this entire file before touching any code.
It will answer every question you have about what we are building, how the
code is organized, and how to work with the team on GitHub.
Do not write a single line of code before finishing this file.

---

## 👥 Team

| Name          | Role                  | Module          |
|---------------|-----------------------|-----------------|
| Ulrich        | Group Lead / Main Menu| `main.c`        |
| Noel*         | Team A Lead           | `syllabus.c`    |
| [Member]      | Team A                | `syllabus.c`    |
| Michel*       | Team B Lead           | `persistence.c` |
| [Member]      | Team B                | `persistence.c` |
| Ange*         | Team C Lead           | `utils.c`       |
| [Member]      | Team C                | `utils.c`       |
| Erika*        | Team D Lead           | `contenu.c`     |
| [Member]      | Team D                | `contenu.c`     |
| Sebastian*    | Team E Lead           | `qcm.c`         |
| [Member]      | Team E                | `qcm.c`         |
| [Member]      | Team E                | `qcm.c`         |

---

## About The Project

C-LMS is a terminal application that simulates a learning platform like Moodle.
Professors build course content and students consume it — all inside the terminal.

The project is built entirely in the C programming language and demonstrates
the following core concepts that every team member is expected to learn
through working on this project:

- Linked lists for dynamic data management
- Recursive algorithms for hierarchical display
- Modular programming across multiple compilation units
- JSON data serialization without any external libraries

The platform has two types of users. The Professor who creates and manages
all course content, and the Student who reads, searches and interacts
with that content.

---

## 🗂️ Project Structure

This is how every file and folder is organized in this repository.
Do not create files outside of this structure without asking the group lead first.

```
UY1-Learning-Management-System/
│
├── src/                  # All implementation files (.c) — where logic lives
│   ├── main.c            # Entry point and menu system (Ulrich)
│   ├── syllabus.c        # Course structure management (Team A)
│   ├── persistence.c     # JSON save and load (Team B)
│   ├── utils.c           # Shared tools and search (Team C)
│   ├── contenu.c         # Lesson display and progress (Team D)
│   └── qcm.c             # Quiz questions and answers (Team E)
│
├── include/              # All header files (.h) — where declarations live
│   ├── syllabus.h        # Core data structures shared by ALL modules
│   ├── persistence.h     # Persistence function declarations
│   ├── utils.h           # Shared constants used by ALL modules
│   ├── contenu.h         # Content function declarations
│   └── qcm.h             # QCM function declarations
│
├── data/
│   └── database.json     # Where course data is saved and loaded from
│
├── CONTRIBUTING.md       # Team coding rules and Git workflow
└── README.md             # This file
```

---

## The Primordial Files — Read This Before Anything Else

Before any team writes a single line of code, two files were created
by the group lead and pushed to the repository. These files are called
primordial files because everything else in the project depends on them.
Think of them as the foundation of a building — every floor built on top
must respect and use that foundation.

These two files are:

- `include/utils.h`
- `include/syllabus.h`

Do not modify these files without first speaking to the group lead.
Changing them affects every single person on the team.

---

### 📄 include/utils.h — The Shared Constants File

**What it is:**
This file contains shared constants that are used across the entire project.
A constant is a fixed value that never changes during the program's execution.
Instead of writing the number 150 directly in your code every time you need
a maximum title length, you use the name MAX_TITLE instead.
This way if the value ever needs to change, it changes in one place
and updates everywhere automatically.

**What it contains:**
- MAX_TITLE — the maximum number of characters allowed in any title
- MAX_CONTENT — the maximum number of characters allowed in lesson content
- MAX_QUESTION — the maximum number of characters in a quiz question
- MAX_OPTION — the maximum number of characters in one quiz answer option

**Why it exists:**
Imagine Team A defines a title as 100 characters long and Team D defines
a title as 200 characters long. When the code is merged, they are
incompatible and the program breaks. utils.h makes sure everyone
agrees on the same numbers from the very beginning.

**How to use it:**
At the top of your .h or .c file, write this line:

```c
#include "utils.h"      // inside an include/ file
#include "../include/utils.h"   // inside a src/ file
```

After that, you can use MAX_TITLE, MAX_CONTENT, MAX_QUESTION and MAX_OPTION
anywhere in your code without defining them yourself.

---

### 📄 include/syllabus.h — The Core Data Structures File

**What it is:**
This file contains the core data structures of the entire platform.
A data structure is a way of organizing information in memory.
In this project, all data is organized using linked lists.

**What a linked list is:**
Think of a treasure hunt. Each clue does not give you the treasure directly —
it gives you the location of the next clue. That is a linked list.
Each item holds its own data AND a pointer to the next item in the chain.
The last item points to NULL which means there is nothing after it.

**What it contains:**
This file defines five structures that represent the entire world of the platform:

- Option — one answer choice in a quiz question. It holds the answer text
  and whether it is correct or wrong. It points to the next option.

- Question — one quiz question. It holds the question text and points to
  its list of options. It also points to the next question.

- Lesson — one lesson inside a chapter. It holds the lesson title,
  the lesson content text, whether the student has completed it,
  and points to its list of quiz questions and to the next lesson.

- Chapter — one chapter inside a course. It holds the chapter title,
  points to its first lesson, and points to the next chapter.

- Course — the entry point of everything. It holds the course title
  and points to the first chapter. From here you can reach every chapter,
  every lesson, every question and every option in the entire platform.

**The full picture of how they connect:**

```
Course
  │
  └──► Chapter 1 ──────────────────────► Chapter 2 ──► NULL
            │                                 │
            ▼                                 ▼
        Lesson 1 ──► Lesson 2 ──► NULL    Lesson A ──► NULL
            │
            ▼
        Question 1 ──► Question 2 ──► NULL
            │
            ▼
        Option A ──► Option B ──► Option C ──► Option D ──► NULL
```

**Why it exists:**
Without this file, every team would invent their own version of what
a Lesson or Chapter looks like. Team A's Lesson would be different from
Team D's Lesson. When the code is merged, nothing would fit together.
syllabus.h makes sure every team uses the exact same definitions.

**How to use it:**
At the top of your .h or .c file, write this line:

```c
#include "syllabus.h"            // inside an include/ file
#include "../include/syllabus.h" // inside a src/ file
```

After that, you can use Course, Chapter, Lesson, Question and Option
in your code without defining them yourself.
Never redefine these structures in your own file.

---

## ✨ The Teams — Purpose, Role and How To Work

---

### 🟦 Team A — syllabus.c / syllabus.h
**3 people**

**Why this team exists:**
Every feature in this platform depends on courses, chapters and lessons
existing in memory. Before a student can read a lesson, someone has to
create it. Before persistence can save data, that data has to exist
as linked lists in memory. Team A builds and manages those linked lists.
Without Team A, there is nothing for any other team to work with.

**What Team A builds:**
Team A implements all the logic for creating and managing the course structure.
This includes creating a course, adding chapters to it, adding lessons to
chapters, deleting and renaming chapters and lessons, and displaying the
full course tree on screen with proper indentation.

The display function is special — it must use recursion, meaning a function
that calls itself, to walk through the nested structure of chapters and lessons
and print them with increasing indentation.

**Why Team A is the most critical:**
Every other team — persistence, contenu, qcm — receives a Course pointer
and works with it. If Team A's linked lists are built incorrectly,
every other module fails. Team A must be the first to have working code.

**How Team A uses the primordial files:**
Team A includes syllabus.h to access the Course, Chapter and Lesson
structures that are already defined there. Team A does not redefine
these structures — they simply write the functions that create and
manipulate them. Team A includes utils.h to use MAX_TITLE and MAX_CONTENT
when declaring character arrays inside their functions.

---

### 🟩 Team B — persistence.c / persistence.h
**2 people**

**Why this team exists:**
Without persistence, every time the program is closed all data disappears.
The professor would have to rebuild the entire course from scratch every
time they open the program. Team B solves this by saving the full course
structure to a file called database.json when the program closes, and
loading it back when the program starts.

**What Team B builds:**
Team B implements two main functions. The first writes the entire course
structure — every chapter, every lesson, every question and every option —
into a JSON formatted text file. The second reads that file back and
reconstructs the full linked list structure in memory so the program
can use it.

Both functions are written in pure C using only file reading and writing
tools that are built into the language. No external libraries are allowed.

**Why Team B is important:**
A platform where data does not persist is not a real platform. Team B
turns this from a demo into a real working application. Without Team B,
the professor's work is lost every session.

**How Team B uses the primordial files:**
Team B includes syllabus.h because their save function receives a Course
pointer and must walk through every Chapter, Lesson, Question and Option
to write them to the file. Their load function must create new Chapter,
Lesson, Question and Option nodes and connect them into a linked list.
They use utils.h constants to know the maximum sizes of strings when
reading data back from the file.

---

### 🟨 Team C — utils.c / utils.h
**2 people**

**Why this team exists:**
Every module in this project needs to do two things constantly —
read input from the user safely, and search through text.
Without a dedicated module for this, every team would write their own
version of input reading and string searching, leading to inconsistency,
bugs, and duplicated work. Team C writes these tools once so everyone
else can use them.

**What Team C builds:**
Team C implements shared utility functions. This includes a safe way to
read text typed by the user, a safe way to read numbers typed by the user,
a function to search for a keyword across all lesson titles and keywords
in the course, and helper functions for comparing and manipulating strings
such as converting text to lowercase for case-insensitive search.

**Why Team C is important:**
Reading user input in C is notoriously error-prone. If done incorrectly
the program can crash or behave unexpectedly. Team C writes one safe,
correct input function that everyone else calls. This protects the
entire project from a common class of bugs.

**How Team C uses the primordial files:**
Team C includes syllabus.h because their search function must receive
a Course pointer and walk through all chapters and lessons to find
keyword matches. They include utils.h for the shared constants
and also add their own function declarations to utils.h so that
every other team can call Team C's functions by including utils.h.

---

### 🟥 Team D — contenu.c / contenu.h
**2 people**

**Why this team exists:**
Building the course structure is not enough on its own.
Students need a clear, navigable way to browse through chapters,
open lessons, read their content, and track their progress.
Team D handles everything related to the student's reading experience.

**What Team D builds:**
Team D implements the browsing and progress system. This includes
displaying the list of chapters for the student to choose from,
displaying the lessons inside a chosen chapter, displaying the full
content of a chosen lesson, marking a lesson as completed after
the student finishes it, and showing the student how many lessons
they have completed out of the total.

**Why Team D is important:**
The student experience is the end goal of the entire platform.
Everything the professor builds exists so the student can consume it.
Team D is the bridge between the data that exists in memory and the
human sitting at the keyboard.

**How Team D uses the primordial files:**
Team D includes syllabus.h because every function they write receives
either a Course, Chapter or Lesson pointer and reads data from it.
They use the is_completed field inside the Lesson structure to track
and display student progress. They include utils.h for the shared
constants when displaying content.

---

### 🟪 Team E — qcm.c / qcm.h
**2 people**

**Why this team exists:**
Reading lessons alone is passive learning. The quiz system forces students
to actively test their understanding of each lesson. Team E builds the
entire quiz experience — from the professor creating questions to the
student answering them and seeing their score.

**What Team E builds:**
Team E implements the full QCM system. On the professor side, this includes
adding a new question to a lesson, and adding four answer options to that
question where each option is marked as either correct or wrong.
On the student side, this includes displaying each question with its options,
reading the student's answer, checking whether it is correct, and showing
the final score at the end of the quiz.

**Why Team E is important:**
The QCM system is one of the explicit requirements from the professor.
It is also what makes the platform interactive rather than just a book viewer.
Without Team E, students have no way to test themselves and the platform
is incomplete according to the project specification.

**How Team E uses the primordial files:**
Team E includes syllabus.h because questions and options are already defined
there as the Question and Option structures. Team E does not redefine these —
they write functions that create new Question and Option nodes and attach them
to the Lesson's questions linked list. They include utils.h for shared constants
and they use Team C's input functions to safely read the student's answer
during a quiz.

---

## 🛠️ How To Build and Run The Full Project

Once all modules are written and merged into dev, the group lead
compiles everything together with this command:

```bash
gcc src/main.c src/syllabus.c src/persistence.c \
    src/utils.c src/contenu.c src/qcm.c \
    -I include -o clms
```

Then run it with:

```bash
./clms
```

---

## 🧪 How To Test Your Module Alone

You do not need main.c to test your own functions.
Create a temporary file in your working folder called test_yourmodule.c.
Inside it, write a simple main function that calls your functions
and prints the results. Compile only your files together with this
temporary file to test your module in isolation.

Delete this temporary test file before your final push to the repository.
It must not appear in the final merged code.

---

## 🌿 Git Workflow — Step by Step

### First time setup — do this once on your computer

```bash
# Tell Git who you are
git config --global user.name "Your Full Name"
git config --global user.email "your_email@gmail.com"

# Clone the project to your computer
git clone git@github.com:Dev-Guy-UIX/UY1-Learning-Management-System.git

# Move into the project folder
cd UY1-Learning-Management-System

# Move to the dev branch
git checkout dev

# Create your own feature branch from dev
git checkout -b feature/syllabus     # Team A
git checkout -b feature/persistence  # Team B
git checkout -b feature/utils        # Team C
git checkout -b feature/contenu      # Team D
git checkout -b feature/qcm          # Team E
```

### Every day — do this every time you sit down to code

```bash
# Step 1 — Always get the latest changes before starting
git pull origin dev

# Step 2 — Write your code

# Step 3 — See what files you have changed
git status

# Step 4 — Stage the files you want to save
git add src/your_file.c include/your_file.h

# Step 5 — Commit with a clear message explaining what you did
git commit -m "[module] what you did"

# Step 6 — Push your work to GitHub
git push origin feature/your-module
```

### Commit message format — follow this exactly

```
[syllabus] Add function to create a new chapter
[persistence] Write JSON save function for lessons
[qcm] Add function to run quiz and show score
[utils] Add keyword search across all lessons
[contenu] Add lesson progress display function
```

### When your module is ready to merge into dev

1. Go to github.com and open the repository
2. Click the button that says Compare and pull request
3. Make sure the base branch is set to dev
4. Write a short description of everything you implemented
5. Click Create pull request
6. Ulrich (group lead) will review your code and merge it

---

## 📐 Coding Standards — Follow These Without Exception

### Naming rules

```c
/* Structures use PascalCase — first letter of each word is capital */
Course, Chapter, Lesson, Question, Option

/* Functions use snake_case with the module name as prefix */
syllabus_add_chapter()
persistence_save()
utils_search_keyword()
contenu_display_lesson()
qcm_run_quiz()

/* Variables use snake_case */
lesson_count, chapter_title, is_completed

/* Constants use ALL_CAPS */
MAX_TITLE, MAX_CONTENT, MAX_QUESTION
```

### Every file must start with this exact header — replace the fields with your info

```c
/**
 * @file filename.c
 * @brief One sentence describing what this file does
 * @author Your Full Name
 * @date 26-05-2026
 */
```

### Every function must have a comment above it explaining what it does

```c
/* Adds a new chapter to the end of the course linked list */
void syllabus_add_chapter(Course *course, char *title) {
    /* your code */
}
```

### Every header file must follow this structure

```c
#ifndef YOURMODULE_H
#define YOURMODULE_H

#include "syllabus.h"
#include "utils.h"

/* your function declarations here */

#endif
```

---

## 📅 Timeline

| Day            | Goal                                                                 |
|----------------|----------------------------------------------------------------------|
| Day 1 — Mon    | Repo setup done, primordial files pushed, all branches created, everyone starts coding |
| Day 2 — Tue    | Each team completes the core functions of their module               |
| Day 3 — Wed    | All modules merged into dev, full program compiled and tested        |
| Day 4 — Thu    | Bug fixes, final cleanup, presentation to professor                  |

---

## 🏫 Academic Context

**Course:** Licence 1 Informatique
**Institution:** Université de Yaoundé 1
**Semester:** Semestre 2, 2025-2026
**Module:** INF132 — Programmation en C