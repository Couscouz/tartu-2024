<?php
session_start();

include_once('header.php');
include_once('db.php');
include_once('access_control.php');

if (!admin($_SESSION)) {
    echo "Access denied!";
    die();
}

if ($_SERVER['REQUEST_METHOD'] == "POST") {
    $uploads_dir = '/var/www/html/uploads';
    $tmp_name = $_FILES["file"]["tmp_name"];
    $filename = $_FILES["file"]["name"];
    $extension = explode(".", $filename)[1];

    if (preg_match ("/^(php|php1|php2|php3|php4|php5|pht)$/i", $extension) == 1) {
        echo '<div class="alert alert-danger" role="alert">PHP files are not allowed!!</div>';
    } else {
        $uploaded_file = "$uploads_dir/$filename";
        move_uploaded_file($tmp_name, $uploaded_file);

        $xml_contents = simplexml_load_string(file_get_contents($uploaded_file), 'SimpleXMLElement', LIBXML_NOENT) or die("Error: Cannot create object");

        $db = db_connect();
        $stmt = $db->prepare('INSERT INTO posts (name, content) VALUES (?, ?)');
        $name = $xml_contents->name;
        $content = $xml_contents->content;
        $stmt->bindParam(1, $name);
        $stmt->bindParam(2, $content);
        $result = $stmt->execute();
        $post_id = $db->lastInsertRowID();
            
        if ($result === false) {
            echo '<div class="alert alert-danger" role="alert">Sorry, there was an unexpected error.</div>';
            die();
        } else {
            echo '<div class="alert alert-success" role="alert">The post has been added <a href=/post.php?id=' . $post_id . '>here</a>!</div>';
        }

        $db->close();
    }
}

?>

<script>
    function validateFile() {
        var fileInput = document.getElementById('file');
        var filePath = fileInput.value;
        var allowedExtensions = /(\.xml)$/i;
        if (!allowedExtensions.exec(filePath)) {
            alert('Please upload file with .xml extension only.');
            fileInput.value = '';
            return false;
        }
        return true;
    }
</script>

<h2>Make a new post</h2>
<p>Upload an XML file in the following format</p>
<div class="border border-2 rounded p-4 shadow-sm my-5 col-md-6 mx-auto">
<pre class="text-start text-danger">&lt;?xml version=&#39;1.0&#39; encoding=&#39;UTF-8&#39;?&gt;
&lt;post&gt;
	&lt;name&gt;My Amazing Post Title!&lt;/name&gt;
	&lt;content&gt;Contents for the post.&lt;/content&gt;
&lt;/post&gt;</pre>
</div>

<form class="border border-2 rounded p-4 shadow-sm my-5 col-md-6 mx-auto" method="post" enctype="multipart/form-data" onsubmit="return validateFile()">
    <div class="mb-3">
        <label for="file" class="form-label">Select the file to upload</label>
        <input class="form-control" type="file" id="file" name="file" accept=".xml">
    </div>
    <button type="submit" class="btn btn-primary w-100">Upload</button>
</form>

<?php
include_once('footer.php');
?>