<html>
<form method="POST">
Enter your name:<input type="text" name="name" size=40 value="<?php echo htmlspecialchars(isset($_POST['name']) ? $_POST['name']:'', ENT_QUOTES) ?>">
<input type="submit">
</form>
<?php
if (isset($_POST['name'])) {
    echo "Hello".htmlspecialchars($_POST['name'], ENT_QUOTES)."!";
}
?>
</html>