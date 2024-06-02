<?php
session_start();

include_once('header.php');
include_once('access_control.php');
include_once('db.php');

if (!admin($_SESSION)) {
    echo "Access denied!";
    die();
}

$db = db_connect();

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    if (isset($_POST["user_id"]) && isset($_POST["isadmin"])) {
        $stmt = $db->prepare('UPDATE users SET isadmin = ? WHERE id = ?');
        $stmt->bindParam(1, $_POST["isadmin"]);
        $stmt->bindParam(2, $_POST["user_id"]);
        $result = $stmt->execute();
    }
}
?>
<script>
    function changePermissions(userid, isadmin) {
        fetch("http://localhost:8000/access.php", {
            method: "POST",
            headers: {
                    "Content-Type": "application/x-www-form-urlencoded",
            },
            body: "user_id=" + userid + "&isadmin=" + (isadmin + 1) % 2,
        }).then(location.reload());
    }
</script>
<h1>Change user privileges</h1>
<form method="post" class="border border-2 rounded p-4 shadow-sm mx-auto col-md-6 my-3">
    <div class="container">
    <?php
    $results = $db->query('SELECT id, username, isadmin FROM users');
    while ($row = $results->fetchArray()) {
        $toggled = "";
        if ($row["isadmin"] == 1) {
            $toggled = "checked";
        }
        echo '<div class="row">';
        echo '<label class="checkbox-inline">';
        echo '<div class="form-check form-switch">';
        echo '<input class="form-check-input" type="checkbox" id="flexSwitchCheckChecked" onchange="changePermissions(' . $row["id"] . ',' . $row["isadmin"] . ')" ' . $toggled . '>';
        echo '<label class="form-check-label" for="flexSwitchCheckChecked">' . $row["username"] . '</label>';
        echo '</div>';
        echo '</label>';
        echo '</div>';
    }
    ?>
    </div>
</form>

<?php
$db->close();
include_once('footer.php');
?>
