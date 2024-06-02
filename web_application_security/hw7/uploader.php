<?php
// Initialize SQLite database
$db = new SQLite3('uploads.db');
$db->exec('CREATE TABLE IF NOT EXISTS file (id INTEGER PRIMARY KEY, filename TEXT, uploaded_at DATETIME)');

// Handle file upload
if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_FILES['file'])) {
    $file = $_FILES['file'];

    // Check file size
    if ($file['size'] > 1048576) { // 1MB in bytes
        die('File is too large. Maximum file size allowed is 1MB.');
    }

    // Save file
    $filename = basename($file['name']);
    $uploadPath = __DIR__ . '/uploads/' . $filename;
    move_uploaded_file($file['tmp_name'], $uploadPath);

    // Store upload record in database
    $stmt = $db->prepare('INSERT INTO uploads (filename, uploaded_at) VALUES (:filename, datetime("now"))');
    $stmt->bindValue(':filename', $filename, SQLITE3_TEXT);
    $stmt->execute();
}

// Handle file deletion
if (isset($_POST['delete']) && is_numeric($_POST['delete'])) {
    $id = $_POST['delete'];
    $stmt = $db->prepare('SELECT filename FROM uploads WHERE id = :id');
    $stmt->bindValue(':id', $id, SQLITE3_INTEGER);
    $result = $stmt->execute();
    $row = $result->fetchArray();
    if ($row) {
        $filename = $row['filename'];
        $uploadPath = __DIR__ . '/uploads/' . $filename;
        if (file_exists($uploadPath)) {
            unlink($uploadPath);
        }
        $stmt = $db->prepare('DELETE FROM uploads WHERE id = :id');
        $stmt->bindValue(':id', $id, SQLITE3_INTEGER);
        $stmt->execute();
    }
}

// Fetch uploaded files from database
$uploads = $db->query('SELECT * FROM uploads ORDER BY uploaded_at DESC');

// HTML rendering
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Secure File Uploader</title>
</head>
<body>
    <h1>File Upload</h1>
    <form action="" method="post" enctype="multipart/form-data">
        <input type="file" name="file" required>
        <button type="submit">Upload</button>
    </form>

    <h2>Uploaded Files</h2>
    <ul>
        <?php while ($upload = $uploads->fetchArray(SQLITE3_ASSOC)): ?>
            <li>
                <a href="uploads/<?php echo $upload['filename']; ?>" target="_blank">
                    <?php echo $upload['filename']; ?>
                </a>
                (Uploaded at: <?php echo $upload['uploaded_at']; ?>)
                <form action="" method="post" style="display:inline">
                    <input type="hidden" name="delete" value="<?php echo $upload['id']; ?>">
                    <button type="submit">Delete</button>
                </form>
            </li>
        <?php endwhile; ?>
    </ul>
</body>
</html>
