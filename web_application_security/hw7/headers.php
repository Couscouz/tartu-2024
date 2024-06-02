<h1>HTTP response header check</h1>

<form method="GET">
Enter URL:
<input type="text" name="url" size=100 value="<?php echo htmlspecialchars($_GET['url'] ?? '', ENT_QUOTES) ?>">
<input type="submit">
</form>
<pre>
<?php
if (isset($_GET['url'])) {
    system("curl --head ".escapeshellarg($_GET['url']));
}
?>
</pre>