<?php
session_start();

include_once('header.php');
include_once('db.php');

if (isset($_GET["id"])) {
    $db = db_connect();

    // handler for posting a new comment
    if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["comment"])) {
        $stmt = $db->prepare('INSERT INTO comments (content, post_id) VALUES (?, ?)');
        $stmt->bindParam(1, $_POST["comment"]);
        $stmt->bindParam(2, $_GET["id"]);
        $result = $stmt->execute();
        
        if ($result === false) {
            echo '<div class="alert alert-danger" role="alert">Sorry, there was an unexpected error.</div>';
        } else {
            echo '<div class="alert alert-success" role="alert">Your comment has been added!</div>';
        }

        $url = 'http://' . getenv('HEADLESS_HOST');
        $webapp = 'http://' . getenv('WEB_DOM');

        $ch = curl_init(); 

        $user = $db->querySingle('SELECT username, password FROM users WHERE id = 2', true);
        
        $act1 = array('type' => 'request', 'url' => $webapp . '/login.php');
        $act2 = array('type' => 'type', 'element' => '#username', 'value' => $user["username"]);
        $act3 = array('type' => 'type', 'element' => '#password', 'value' => $user["password"]);
        $act4 = array('type' => 'click', 'element' => 'button#submit');
        $act5 = array('type' => 'request', 'url' => $webapp . '/post.php?id=' . $_GET["id"]);
        
        $data = array('actions' => [$act1, $act2, $act3, $act4, $act5], 'browser' => 'chrome');
        $data = json_encode($data);
        
        // Set cURL options 
        curl_setopt($ch, CURLOPT_URL, $url); 
        curl_setopt($ch, CURLOPT_POST, 1); 
        curl_setopt($ch, CURLOPT_HTTPHEADER, [
            'Content-type: application/json',
            'X-Auth: ' . getenv('HEADLESS_AUTH')
        ]);
        curl_setopt($ch, CURLOPT_POSTFIELDS, $data); 
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true); 
        
        // Execute cURL session 
        $response = curl_exec($ch); 
        
        // Close cURL session 
        curl_close($ch); 
        
    }

    // handler for deleting a comment
    if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["remove_comment"])) {
        $stmt = $db->prepare('DELETE FROM comments WHERE id = ?');
        $stmt->bindParam(1, $_POST["remove_comment"]);
        $result = $stmt->execute();
        
        if ($result === false) {
            echo '<div class="alert alert-danger" role="alert">Sorry, there was an unexpected error.</div>';
        } else {
            echo '<div class="alert alert-success" role="alert">The comment has been deleted!</div>';
        }
    }
    
    // show post details
    $stmt = $db->prepare('SELECT * FROM posts WHERE id = ?');
    $stmt->bindParam(1, $_GET["id"]);
    $post = $stmt->execute()->fetchArray();
    echo "<article class=\"blog-post border rounded p-4 mb-4\">";
    echo "<h1 class=\"display-5 fw-bold mb-3\">" . $post["name"] . "</h1>";
    echo "<p class=\"text-muted\">" . date('Y-m-d') . "</p>";
    echo "<p class=\"lead\">" . $post["content"] . "</p>";
    echo "</article>";

    // show currently submitted comments
    echo "<h2>Comments</h2>";
    $stmt = $db->prepare('SELECT * FROM comments WHERE post_id = ?');
    $stmt->bindParam(1, $_GET["id"]);
    $comments = $stmt->execute();
    while($comment = $comments->fetchArray()) {
        echo "<article class=\"blog-post border rounded p-4 mb-4\">";
        echo "<p class=\"lead\">" . $comment["content"] . "</p>";
        echo "<form method=\"POST\">";
        echo "<input name=\"remove_comment\" type=\"hidden\" value=\"" . $comment["id"] . "\">";
        echo "<button type=\"submit\" class=\"btn btn-danger\">Delete</button>";
        echo "</form>";
        echo "</article>";
    }



    $db->close();
}
?>

<form id="comment-form" method="POST" class="border rounded p-4 mb-4">
    <div class="mb-3">
        <label for="comment" class="form-label">Comment:</label>
        <textarea id="comment" name="comment" class="form-control" rows="3" required></textarea>    
    </div>
    <button type="submit" class="btn btn-primary">Submit Comment</button>
</form>


<?php

include_once('footer.php');
?>