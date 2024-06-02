<?php 
    $COOKIE_NAME = "__Host-account";
    
    function validateCookie($cookie) {
        return (strlen($cookie) == 32 && ctype_xdigit($cookie));
    }

    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        //Form retrieve
        $username = $_POST["username"];
        $password = $_POST["password"];
        if ($username == "user" && $password == "pass") {
            //Generating cookie value
            $temp = random_bytes(16);
            $cookie_value = bin2hex($temp);

            //Setting the cookie
            setcookie($COOKIE_NAME, $cookie_value, [
                'secure' => true,
                'path' => '/'
            ]);
            header("Location: hw01.php");
            exit;
        } else {
            echo "<h4>Login incorrect!</h4>";
        }

    } else if ($_SERVER["REQUEST_METHOD"] == "GET") {       
        if (isset($_GET["action"]) && $_GET["action"] == "logout" && isset($_COOKIE[$COOKIE_NAME])) {
            //Deleting cookie
            setcookie($COOKIE_NAME, '', [
                'secure' => true,
                'path' => '/'
            ]);
            header("Location: hw01.php");
            exit;
        }
    } else {
        //Not valid method
        http_response_code(405);
        echo "Error, only GET/POST supported on this Homework1 website";
        exit;
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Homework 1</title>
</head>
<body>
    <h2>Homework 1 | COUZI Remi<h2>
    <?php
        if (isset($_COOKIE[$COOKIE_NAME]) && validateCookie($_COOKIE[$COOKIE_NAME])) {
            //if good cookie set (logged), print logout button
            echo "<h4>Hello user!</h4>";
            echo "<form action='hw01.php' method='get'>
                        <input type='hidden' name='action' value='logout'>
                        <button type='submit'>Logout</button>
                </form>";
        } else {
            //if not logged in, print login form
            echo "<form method='post' action='hw01.php' onsubmit='return validateForm()'>
                    <input type='text' name='username' id='username' placeholder='Username'>
                    <input type='password' name='password' id='password' placeholder='Password'>
                    <input type='submit' name='submit' value='Login'>
                </form>";
        } 
    ?>
    
    <script>
        validateForm = () => {
            let usernameInput = document.getElementById("username").value;
            let passwordInput = document.getElementById("password").value;
            if (usernameInput.trim() == "" && passwordInput.trim() == "") {
                alert("Please enter a username and a password");
                return false;
            } else if (usernameInput.trim() == "") {
                alert("Please enter a username");
                return false;
            } else if (passwordInput.trim() == "") {
                alert("Please enter a password");
                return false;
            }
            return true;
        }
    </script>
</body>
</html>
