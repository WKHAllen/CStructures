# CStructures

A collection of data structures in C, for my own benefit.

## About

This repository contains a number of simple data structures for the C language. All structures are designed to be dynamic in the sense that they are capable of expanding to hold as many values as needed. Each structure is also able to store values of any data type.

## Data structures

### [Stack](/src/stack.h)

Stack type. Implemented like a linked list.

### [Queue](/src/queue.h)

Queue type. Implemented like a linked list.

### [Linked List](/src/linkedlist.h)

Linked list type. Contains a reference to both the head and tail, which allows for optimization of several useful functions.

### [List](/src/list.h)

List type. Based on Python's list object. Contains functions for just about everything one could possibly need. Size is doubled when more space is needed and halved when enough is left unused.

### [HashTable](/src/hashtable.h)

Hash table type. Based on Python's dictionary object. Contains functions for just about everything one could possibly need. Size is doubled when more space is needed and halved when enough is left unused. Linear probing is used to resolve collisions. Hashing is implemented by summing the binary data of a key.

### [BinaryTree](/src/binarytree.h)

Binary tree type.
