<?php

    //configuration
    require("../includes/config.php");
    
    //if redirected from form
    
    if( $_SERVER["REQUEST_METHOD"] =="POST")
    {
        //check for empty fields
        if(empty($_POST["symbol"]))
        {
            apologize("You must select a stock symbol to sell.");
        }
        if(empty($_POST["num_of_shares"]))
        {
            apologize("You must select number of stock to sell.");
        }
        
        //lookup for symbol
        $stock = lookup($_POST["symbol"]);
        
        //shares in portfolios 
        $sql_shares = query("SELECT `shares` FROM `portfolios` WHERE `id` = ? AND  `symbol` = ?", $_SESSION['id'], $_POST["symbol"]);
        $shares = $sql_shares[0]["shares"];
        
        //how many user wanted to sell
        $sell_share  = $_POST["num_of_shares"];
        
        //check if user have appropriate number of shares
        if( $sell_share > $shares || $sell_share  <= 0)
        {
            apologize("You have".$shares ." shares. Select number appropritaly!");
        }
        
        //looup for the current stock price then delete
        $pr = $stock["price"];
        
        //update cash USERS table
        $cash = $sell_share * $pr;
        query("UPDATE `users` SET `Cash` = `Cash` + $cash WHERE `id` = ?", $_SESSION['id']);
        
        //Delete record of stock PORTFOLIOS table
        if($sell_share == $shares){
            $sql_delete = query("DELETE  FROM `portfolios` WHERE `id` = ? AND  `symbol` = ?", $_SESSION['id'], $stock['symbol']); //$_POST["symbol"]);
        }
        else{ 
            //update the stock PORTFOLIOS table
            $sql_update = query("UPDATE `portfolios` 
                SET `shares` = `shares` - $sell_share 
                WHERE `id` = ? AND  `symbol` = ?", 
                $_SESSION['id'],$_POST["symbol"]);
        }
        
        //insert transaction in history table
        query("INSERT INTO `history`
        (`id`, `symbol`, `shares`, `price`, `transaction`) 
        VALUES (?, ?, ?, ?, ?)" ,
        $_SESSION['id'],
        $stock['symbol'],
        $sell_share,
        $cash,
        strtoupper('SELL'));
        
        redirect("/");
        
    }
    else
    {
        //get stock to sell from protfolio
        $sql_protfolio = query("SELECT * FROM `portfolios` WHERE `id` = ?", $_SESSION['id']);
        
        //prepare portfolio data to display in drop down menu
        foreach ($sql_protfolio as $row)
        {
            //collect associated information of the record
            $stock = lookup($row["symbol"]);
            
            //if symbol found
            if ($stock !== false)
            {
                $positions[] = [
                    "symbol" => $row["symbol"],
                    "name" => $stock["name"],
                    "shares" => $row["shares"],
                    "price" => $stock["price"]
                ];
            }
        }
        
        if(isset($positions)){
            //display form
            render("sell_form.php", ["position" => $positions, "title"=>"Sell"]);
       }else
       {
            apologize("No share to sell");
       }     
    }
?>


