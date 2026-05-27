# UY1 Learning Management System (UY1-LMS)

A console-based learning management platform built in C, developed as part of the
end-of-semester project for Licence 1 Informatique at the University of Yaoundé 1.

---

## 📚 About The Project

C-LMS is a terminal application that simulates a learning platform (like Moodle)
where professors can build course content and students can consume it.

The project demonstrates core C programming concepts including:
- Linked lists for dynamic data management
- Recursive algorithms for hierarchical display
- Modular programming across multiple compilation units
- JSON serialization without external libraries

---

## 👥 Team

| Name | Role | Module |
|------|------|--------|
| Ulrich | Group Lead / Main Menu | `main.c` |
| [Noel] | Team A | `syllabus.c` |
| [Name] | Team A | `syllabus.c` |
| [Name] | Team A | `syllabus.c` |
| [Name] | Team B | `persistence.c` |
| [Name] | Team B | `persistence.c` |
| [Name] | Team C | `utils.c` |
| [Name] | Team C | `utils.c` |
| [Name] | Team D | `contenu.c` |
| [Name] | Team D | `contenu.c` |
| [Name] | Team E | `qcm.c` |
| [Name] | Team E | `qcm.c` |

---

## ✨ Features

### Professor Space
- Create a course with chapters and lessons
- Add, delete and rename chapters and lessons at any level
- Attach QCM quiz questions to lessons (4 options per question)
- Add keywords to lessons for student search
- Save the full course structure to `data/database.json`
- Visualize the complete course tree with automatic indentation

### Student Space
- Browse available courses and read lesson content
- Search lessons by keyword
- Answer QCM quizzes with recorded results
- Mark lessons as completed and track progress

---

## 🗂️ Project Structure