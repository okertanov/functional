<?php

function finalize($rc, $fc)
{
    echo "<script language=\"javascript\" type=\"text/javascript\">window.top.window.upload_done($rc, \"$fc\");</script>";
    exit;
}

$result = 0;
$file = $_FILES['files'];

$path_parts = pathinfo($file['name']);
$file_name = $path_parts['basename'];
$file_ext  = $path_parts['extension'];
$tmp_name  = $file['tmp_name'];
$md5_name  = md5_file($tmp_name).".".$file_ext;
$post_back  = "";

$white_list = array("jpg", "jpeg", "png", "gif");
$file_type_matched = 0;
foreach ($white_list as $wfile)
{
    if(preg_match("/$wfile\$/i", $file_ext))
    {
        $file_type_matched = 1;
    }
}

if($file_type_matched)
{
    $destination_path = getcwd().DIRECTORY_SEPARATOR."i".DIRECTORY_SEPARATOR;
    $target_path = $destination_path . $md5_name;

    if(@move_uploaded_file($tmp_name, $target_path))
    {
        $post_back = "http://replica.espectrale.com/i/".$md5_name;
        $result = 1;
    }
    else
    {
        $post_back = "Failed to upload.";
    }
}
else
{
    $post_back = "Invalid image type. " . $file_name;
}

finalize($result, $post_back);

?>
