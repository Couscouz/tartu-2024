<?php
session_start();

include_once('header.php');
include_once('access_control.php');
include_once('db.php');

if (!user($_SESSION)) {
    echo "Access denied!";
    die();
}
    
if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["post_id"])) {
    $db = db_connect();
    $url = 'http://' . getenv('HEADLESS_HOST');
    $webapp = 'http://' . getenv('WEB_DOM');

    $ch = curl_init(); 

    $admin = $db->querySingle('SELECT username, password FROM users WHERE id = 1', true);
    
    $act1 = array('type' => 'request', 'url' => $webapp . '/login.php');
    $act2 = array('type' => 'type', 'element' => '#username', 'value' => $admin["username"]);
    $act3 = array('type' => 'type', 'element' => '#password', 'value' => $admin["password"]);
    $act4 = array('type' => 'click', 'element' => 'button#submit');
    $act5 = array('type' => 'request', 'url' => $webapp . '/post.php?id=' . $_POST["post_id"]);
    
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
    
    if ($result === FALSE) {
        echo '<div class="alert alert-danger" role="alert">Sorry, there was an error sending your message.</div>';
    } else {
        echo '<div class="alert alert-success" role="alert">Thank you, an Administrator will review the submitted post very soon!</div>';
    }
    
    // Close cURL session 
    curl_close($ch); 
    $db->close();
}
        
?>
<h1>Report a post</h1>
<br>
<h5>Please report any posts to the Administrator, if you think they should be reviewed!</h5>
<br>

<form method="post" class="border border-2 rounded p-4 shadow-sm mx-auto col-md-6 my-3">
    <div class="mb-3">
        <label for="post_id" class="form-label">Post ID:</label>
        <input type="text" class="form-control" id="post_id" name="post_id">
    </div>

    <div class="mb-3">
        <label for="message" class="form-label">Message:</label>
        <textarea class="form-control" id="message" name="message" rows="3"></textarea>
    </div>

    <button type="submit" class="btn btn-primary btn-block">Send</button>
</form>


<?php
include_once('footer.php');
?>