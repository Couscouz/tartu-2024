<?php
session_start();

include_once('header.php');
include_once('access_control.php');
include_once('db.php');

if (!admin($_SESSION)) {
    echo "Access denied!";
    die();
}

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    if (isset($_POST["password"])) {
        $db = db_connect();
        $stmt = $db->prepare('UPDATE users SET password = ? WHERE id = ?');
        $new_pwd = $_POST["password"];
        $user_id = $_SESSION["logged_in"];
        $stmt->bindParam(1, $new_pwd);
        $stmt->bindParam(2, $user_id);
        $result = $stmt->execute();

        if ($result === false) {
            echo '<div class="alert alert-danger" role="alert">Sorry, there was an unexpected error.</div>';
            die();
        }
    }
    
    if (isset($_POST["username"])) {
        $db = db_connect();
        $stmt = $db->prepare('UPDATE users SET username = ? WHERE id = ?');
        $new_usrname = $_POST["username"];
        $user_id = $_SESSION["logged_in"];
        $stmt->bindParam(1, $new_usrname);
        $stmt->bindParam(2, $user_id);
        $result = $stmt->execute();

        if ($result === false) {
            echo '<div class="alert alert-danger" role="alert">Sorry, there was an unexpected error.</div>';
            die();
        }
    }

    echo '<div class="alert alert-success" role="alert">Username and password changed successfully!</div>';
}
?>
<h1>Edit the username and password for your account</h1>
<div class="row justify-content-center">
    <div class="col-md-6">
        <form class="border border-2 rounded p-4 shadow-sm" method="post">
            <div class="mb-3">
                <label for="username" class="form-label">New username:</label>
                <input type="username" class="form-control" id="username" name="username" required>
            </div>
            <div class="mb-3">
                <label for="password" class="form-label">New password:</label>
                <input type="password" class="form-control" id="password" name="password" required>
            </div>
            <button id="submit" type="submit" class="btn btn-primary">Change</button>
        </form>
    </div>
</div>

<?php
include_once('footer.php');
?>