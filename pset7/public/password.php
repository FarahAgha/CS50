<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //user name isnt blank else apologize
        if($_POST['currentpassword']== '' || $_POST['newpassword'] == '' )
        {
            apologize("All fields are mandatory");
            
        } //password should be same else apologize ("Password mismatch")
        else if ($_POST['newpassword'] != $_POST['confirmation'])
        {
            apologize("New Password Mismatch");
        }
        
        //current password in database 
        $sql_password = query("SELECT `hash` FROM `users` WHERE `id` = ?",  $_SESSION['id']);
        $curr_pass = $sql_password[0]["hash"];
        
        
        //crypted current password given by use == password in the database
        if (crypt($_POST["currentpassword"], $curr_pass) == $curr_pass)
        {
            // insert user into database
            $res = QUERY( "UPDATE users  SET `hash`= ?  WHERE `id` = ?",  CRYPT($_POST['newpassword']),  $_SESSION['id']  );  
            
            //if query failed      
            if( $res === false )
            {   
                apologize("Password not changed");
            }
            
        }else { //display password is incorrect
            apologize("Incorrect Password!!");
        }
        
        //redirect to display index page
        redirect("/"); 
    }
    else
    {
        // else render form
        render("password_form.php", ["title" => "Change Password"]);
    }

?>
