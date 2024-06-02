<?php
session_start();
ob_start(); // Start output buffering

include_once('header.php');
include_once('db.php');

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    if (isset($_POST["username"]) && isset($_POST["password"])) {
        $db = db_connect();
        $stmt = $db->prepare('SELECT id, username, password, isadmin FROM users WHERE username = ?');
        $stmt->bindParam(1, $_POST["username"]);
        $user = $stmt->execute()->fetchArray();

        if ($_POST["password"] == $user["password"]) {
            $_SESSION["logged_in"] = $user["id"];
            if ($user["isadmin"] == 1) {
                $_SESSION["isadmin"] = 1;

                // We should protect the admin cookie a little better than we did for the user...
                setcookie(session_name(), session_id(), ["httpOnly" => true, "SameSite" => "strict"]);
                header("Location: index.php");
                exit;
            } else {
                $_SESSION["isadmin"] = 0;
                header("Location: index.php");
                exit;
            }
        } else {
            echo '<div class="alert alert-danger" role="alert">Wrong username or password!</div>';
        }
        $db->close();
    }
} else if ($_SERVER["REQUEST_METHOD"] == "GET") {
    // route the user to the main page, if they are already logged in
    if (isset($_SESSION["logged_in"])) {
        header("Location: index.php");
        exit;
    }
}

ob_end_flush(); // Flush the output buffer and turn off output buffering


include_once('footer.php');
?>
<div class="container mt-5">
    <div class="row justify-content-center">
        <div class="col-md-6">
            <div class="card">
                <div class="card-body">
                    <h2 class="card-title text-center">Login</h2>
                        <form method="post">
                            <label class="form-label" for="username">Username:</label><br>
                            <input class="form-control" type="text" id="username" name="username" required><br>
                            <label class="form-label" for="password">Password:</label><br>
                            <input class="form-control" type="password" id="password" name="password" required><br>
                            <button class="btn btn-primary my-3" id="submit" type="submit">Login</button>
                        </form>
                    </div>
                </div>
            </div>
        </div>
    </div>     
</div>                       