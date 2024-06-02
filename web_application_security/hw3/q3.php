<?php

//Check HTTP Referer header
if ($_SERVER['REQUEST_METHOD'] == 'POST') { //Checks if POST
    if (isset($_SERVER['HTTP_REFERER'])) { // Checks if Referer header is set
        if (parse_url($_SERVER['HTTP_REFERER'], PHP_URL_HOST) !== $_SERVER['SERVER_NAME']) { //Compare host current server host
            die("Cross-site request!"); //Die if hosts don't match
        }
    } else {
        die("Referer header not set!"); //Die if Referer header is not set
    }
}

//----------------------------------------------

$db = new SQLite3('.comments.sqlite', SQLITE3_OPEN_CREATE | SQLITE3_OPEN_READWRITE);
// Create a table.
$db->query('CREATE TABLE IF NOT EXISTS "comments" (
  "id" INTEGER PRIMARY KEY,
  "comment" VARCHAR,
  "ip" VARCHAR,
  "added" DATETIME
)');

function S($text) {
    return htmlspecialchars($text, ENT_QUOTES);
}

// add comment if POSTed + token exist + token is correct
if ( isset($_POST['comment']) ) {
    // Insert data
    $db->exec('BEGIN');
    $sql = 'INSERT INTO "comments" ("comment", "ip", "added") VALUES (?, ?, datetime("now","localtime"))';
    $statement = $db->prepare($sql);
    $statement->bindValue(1, substr($_POST['comment'], 0, 70));
    $statement->bindValue(2, $_SERVER['REMOTE_ADDR']);
    $statement->execute();
    $db->exec('COMMIT');
}


?>
<!DOCTYPE html>
<html>
<head>
    <title>Write a comment</title>
</head>
<body>

    <h1>Write a comment</h1>
    <textarea form="commentForm" id="commentId" name="comment" placeholder="Add your comment..." rows="3" cols="30"></textarea>
    <form method="POST" name="commentForm" action="" id="commentForm">
        <input type="submit" value="Add">
    </form>
    <h2>Comments</h2>
    <ul>
    <?php

        $statement = $db->prepare('SELECT * FROM "comments" ORDER BY "added" DESC LIMIT 30');
        $result = $statement->execute();
        while ($row = $result->fetchArray(SQLITE3_ASSOC)) {
            echo '<li>['.S($row['added']).'] ('.S($row['ip']).') '.S($row['comment']).'</li>';
            echo "\n";
        }

        $db->close();

    ?>
    </ul>

</body>
</html>
