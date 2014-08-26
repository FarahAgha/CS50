<?php
    
    //configuration
    require("../includes/config.php");
    
    //if form was submitted
    if( $_SERVER["REQUEST_METHOD"]== "POST")
    {
        //You must specify a stock to buy.
        if(empty ($_POST["symbol"] )){
            
            apologize("You must specify a stock to buy.");
        }
        //You must specify a number of shares.
        if(empty($_POST["shares"])){
            
            apologize("You must specify a number of shares.");
        }
        
        //Collect stock info for symbol
        $stock = lookup($_POST["symbol"]);
        
        //Check for symbol
        if( $stock === false)
        {
            apologize("Symbol not found.");
        }
        
        //calculate total cost of stock
        $shares = $_POST["shares"];
        $total = $shares * $stock["price"];
         
        
        //collect cash info from "user"  
        $sql_cash = query("SELECT * FROM `users` WHERE `id` = ?",  $_SESSION['id']);
        $cash = $sql_cash[0]["Cash"];
        
        
        if($total > $cash)
        {
            apologize("You can't afford that. You have $".$cash." and shares cost is $".$total);
        }
        
        //insert  or update the record
        query("INSERT INTO portfolios 
            (`id`, `symbol`, `shares`) 
            VALUES (?, ?, ?)
            ON DUPLICATE KEY 
            UPDATE  `shares` = `shares` + ?" , 
            $_SESSION['id'], strtoupper($stock['symbol']), $shares, 
            $shares );
  
        // update cash
        query("UPDATE users SET cash = cash - ? WHERE id = ?", $total,  $_SESSION['id']);
        
        //insert transaction in history
        query("INSERT INTO `history`
        (`id`, `symbol`, `shares`, `price`, `transaction`) 
        VALUES (?, ?, ?, ?, ?)" ,
        $_SESSION['id'],
        strtoupper($stock['symbol']),
        $shares,
        $total,
        strtoupper('BUY'));
        
        //redirect to index page
        redirect("/");
    }
    else
    {
        //redirect to display form
        render("buy_form.php", ["title" => "Buy"]);
    }
?>
