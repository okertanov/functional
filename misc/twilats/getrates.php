<?php
$hostname = "localhost";
$username = "twilats";
$password = "SecurePassword";
$database = "twilats";
$table    = "rates";

mysql_connect($hostname,$username,$password) or die("Can't connect to Database.");
mysql_select_db($database) or die(mysql_error());
$query = "SELECT UNIX_TIMESTAMP(date)*1000 as uxdate, eur1,eur2,eur3,sek1*10 as sek1,sek2*10 as sek2,sek3*10 as sek3,usd1,usd2,usd3 FROM $table where YEAR(date) = '2011' ORDER BY date";
$res = mysql_query($query) or die(mysql_error());
$number = mysql_num_rows($res);

$startData = '[';
$startChartDataEur1 = '{ label: "1 EUR Buy", data:[';
$startChartDataEur2 = '{ label: "1 EUR Sell", data:[';
$startChartDataEur3 = '{ label: "1 EUR LB", data:[';
$startChartDataSek1 = '{ label: "10 SEK Buy", data:[';
$startChartDataSek2 = '{ label: "10 SEK Sell", data:[';
$startChartDataSek3 = '{ label: "10 SEK LB", data:[';
$startChartDataUsd1 = '{ label: "1 USD Buy", data:[';
$startChartDataUsd2 = '{ label: "1 USD Sell", data:[';
$startChartDataUsd3 = '{ label: "1 USD LB", data:[';
$lineChartDataEur1 = '';
$lineChartDataEur2 = '';
$lineChartDataEur3 = '';
$lineChartDataSek1 = '';
$lineChartDataSek2 = '';
$lineChartDataSek3 = '';
$lineChartDataUsd1 = '';
$lineChartDataUsd2 = '';
$lineChartDataUsd3 = '';
$endChartData = ']}';
$endData = ']';

if ($number > 0)
{
    mysql_data_seek($res, 0);
    while ($row=mysql_fetch_array($res))
    {
        $eurLine = '['.($row['uxdate']).','.$row['eur1'].']';
        $lineChartDataEur1 = $lineChartDataEur1.(strlen($lineChartDataEur1)?',':'').$eurLine;
        $eurLine = '['.($row['uxdate']).','.$row['eur2'].']';
        $lineChartDataEur2 = $lineChartDataEur2.(strlen($lineChartDataEur2)?',':'').$eurLine;
        $eurLine = '['.($row['uxdate']).','.$row['eur3'].']';
        $lineChartDataEur3 = $lineChartDataEur3.(strlen($lineChartDataEur3)?',':'').$eurLine;
        $sekLine = '['.($row['uxdate']).','.$row['sek1'].']';
        $lineChartDataSek1 = $lineChartDataSek1.(strlen($lineChartDataSek1)?',':'').$sekLine;
        $sekLine = '['.($row['uxdate']).','.$row['sek2'].']';
        $lineChartDataSek2 = $lineChartDataSek2.(strlen($lineChartDataSek2)?',':'').$sekLine;
        $sekLine = '['.($row['uxdate']).','.$row['sek3'].']';
        $lineChartDataSek3 = $lineChartDataSek3.(strlen($lineChartDataSek3)?',':'').$sekLine;
        $usdLine = '['.($row['uxdate']).','.$row['usd1'].']';
        $lineChartDataUsd1 = $lineChartDataUsd1.(strlen($lineChartDataUsd1)?',':'').$usdLine;
        $usdLine = '['.($row['uxdate']).','.$row['usd2'].']';
        $lineChartDataUsd2 = $lineChartDataUsd2.(strlen($lineChartDataUsd2)?',':'').$usdLine;
        $usdLine = '['.($row['uxdate']).','.$row['usd3'].']';
        $lineChartDataUsd3 = $lineChartDataUsd3.(strlen($lineChartDataUsd3)?',':'').$usdLine;
    };
}

echo $startData;
#echo $startChartDataEur1.$lineChartDataEur1.$endChartData.',';
echo $startChartDataEur2.$lineChartDataEur2.$endChartData.',';
echo $startChartDataEur3.$lineChartDataEur3.$endChartData.',';
#echo $startChartDataSek1.$lineChartDataSek1.$endChartData.',';
echo $startChartDataSek2.$lineChartDataSek2.$endChartData.',';
echo $startChartDataSek3.$lineChartDataSek3.$endChartData.',';
#echo $startChartDataUsd1.$lineChartDataUsd1.$endChartData.',';
echo $startChartDataUsd2.$lineChartDataUsd2.$endChartData.',';
echo $startChartDataUsd3.$lineChartDataUsd3.$endChartData;
echo $endData;

?>
