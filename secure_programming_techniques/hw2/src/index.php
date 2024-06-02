<?php
session_start();

include_once('header.php');
include_once('db.php');
require_once 'vendor/autoload.php';

$db = db_connect();

if (user($_SESSION)) {
  $username = $db->querySingle("SELECT username FROM users WHERE id = " . $_SESSION["logged_in"]);
  $loader = new \Twig\Loader\ArrayLoader([
    'greeting' => '<h1>Hello, ' . $username . '!</h1>',
  ]);
  $twig = new \Twig\Environment($loader);
  echo $twig->render('greeting');
}

echo "<h1>Thoughts about Tulnukas 2:</h1>";

$results = $db->query('SELECT * FROM posts ORDER by id DESC');
while ($row = $results->fetchArray()) {
  echo "<article class=\"border border-2 rounded p-4 shadow-sm\">";  echo "<h2 class=\"display-5 fw-bold mb-3\">" . $row["name"] . "</h2>";
  echo "<p class=\"text-muted\">" . date('Y-m-d') . "</p>";
  echo "<p class=\"lead\">" . $row["content"] . "</p>";
  echo "<a href=\"/post.php?id=" . $row["id"] . "\" class=\"btn btn-primary\">Read More</a>";
  echo "</article>";
  echo "<br>";
}

include_once('footer.php');
?>