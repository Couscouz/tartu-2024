<?php
    session_start();

    include_once('db.php');

    function admin() {
        if (isset($_SESSION["isadmin"]) && $_SESSION["isadmin"] == 1) {
            return true;
        }
        return false;
    }

    function user() {
        if (isset($_SESSION["logged_in"])) {
            // check if users permissions have changed and update session cookie if necessary
            $db = db_connect();
            $_SESSION["isadmin"] = $db->querySingle("SELECT isadmin FROM users WHERE id = " . $_SESSION["logged_in"]);
            $db->close();
            return true;
        }
        return false;
    }

?>