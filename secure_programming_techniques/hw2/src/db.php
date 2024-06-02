<?php

function db_connect() {
    // sqlite db
    $db = new SQLite3('/data/blog.db');
    return $db;
}

function db_init() {
    $db = db_connect();
    $db->exec('PRAGMA foreign_keys = ON');
    $db->exec('CREATE TABLE IF NOT EXISTS posts (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, content TEXT)');
    $db->exec('CREATE TABLE IF NOT EXISTS comments (id INTEGER PRIMARY KEY AUTOINCREMENT, content TEXT, post_id INTEGER, FOREIGN KEY(post_id) REFERENCES posts(id))');
    $db->exec('CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, password TEXT, isadmin BOOLEAN)');
    $db->close();
}

//db_init();
?>