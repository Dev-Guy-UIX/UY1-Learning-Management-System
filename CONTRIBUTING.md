# Contributing Guide — UY1-LMS Project

## Branch Naming
- feature/syllabus
- feature/persistence
- feature/qcm
- feature/contenu
- feature/utils

## Commit Message Format
[module] Short description of what you did

Examples:
[syllabus] Add function to delete a chapter
[qcm] Create struct for question and answers
[persistence] Write JSON export for chapters

## Naming Rules
- Structures: PascalCase → Lesson, Chapter, Course
- Functions: snake_case with module prefix → syllabus_add_chapter()
- Variables: snake_case → lesson_count, chapter_title
- Constants: ALL_CAPS → MAX_TITLE, MAX_CONTENT

## Before Every Commit
- Your code must compile without errors
- Add a comment explaining every function


**The File Header Template**

/**
 * @file syllabus.c
 * @brief Manages course structure using linked lists
 * @author [Your Name]
 * @date 25-05-2026
 */