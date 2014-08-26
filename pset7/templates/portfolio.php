<?php
    
    //collect share information from "portfolio" table store in an array (e.g. row)
    //$sql_shares = query("SELECT * FROM `portfolios` WHERE `id` = ?",  $_SESSION['id']);
    
    //collect cash info from "user"  
    //$sql_cash = query("SELECT * FROM `users` WHERE `id` = ?",  $_SESSION['id']);
    
?>
<ul class="nav nav-pills" >
    <li><a href="quote.php">Quote</a></li>
    <li><a href="buy.php">Buy</a></li>
    <li><a href="sell.php">Sell</a></li>
    <li><a href="history.php">History</a></li>
    <li><a href="addcash.php">Deposite Fund</a></li>
    <li><a href="password.php">Change Password</a></li>
    <li><a href="logout.php"><strong>Log Out</strong></a></li>
</ul>


<table class="table table-striped">

    <thead >
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>TOTAL</th>
        </tr>
    </thead>

    <tbody align="left">
        <!-- display shares info stored in an array (row) -->
        <?php  
            
            foreach ($positions as $position):  ?> 
            <tr>
                <td><?= $position["symbol"] ?></td>
                <td><?= $position["name"] ?></td>
                <td><?= $position["shares"] ?></td>
                <td><?= $position["price"] ?></td>
                <td><?= $position["price"]*$position["shares"]  ?></td>
            </tr>

        <?php endforeach ?>
        <tr>
            
            <td colspan="4">CASH</td>
            <td>
                <!-- display cash information -->
                <? print($cash); ?>
            </td>
        </tr>    
    <tbody>
</table>



