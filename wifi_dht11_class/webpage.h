const char index_html[] PROGMEM = R"webpage(
<!DOCTYPE HTML><html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<script src="https://code.highcharts.com/8.0/highcharts.js"></script>
<style>
body {
min-width: 300px;
max-width: 800px;
height: 400px;
margin: 0 auto;
}
h2 {
font-family: Arial;
font-size: 2.5rem;
text-align: center;
}
</style>
</head>
<body>
<h2>ESP8266 Weather Station Chart</h2>
<div id="temperature-chart" class="container"></div>
<div id="fahrenheit-chart" class="container"></div>
<div id="humidity-chart" class="container"></div>
</body>
<script>
var chartT = new Highcharts.Chart({
chart:{ renderTo : 'temperature-chart' },
title: { text: 'Temperature in Degree Celsius' },
series: [{
showInLegend: false,
data: []
}],
plotOptions: {
line: { animation: false,
dataLabels: { enabled: true }
},
series: { color: '#059e8a' }
},
xAxis: { type: 'datetime',
dateTimeLabelFormats: { second: '%H:%M:%S' }
},
yAxis: {
title: { text: 'Temperature (Celsius)' }
},
credits: { enabled: false }
});
setInterval(function ( ) {
var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
if (this.readyState == 4 && this.status == 200) {
var x = (new Date()).getTime(),
y = parseFloat(this.responseText);
if(chartT.series[0].data.length > 50) {
chartT.series[0].addPoint([x, y], true, true, true);
} else {
chartT.series[0].addPoint([x, y], true, false, true);
}
}
};
xhttp.open("GET", "/temperature", true);
xhttp.send();
}, 1000 ) ;

var chartF = new Highcharts.Chart({
chart:{ renderTo:'fahrenheit-chart' },
title: { text: 'Temperature in Fahrenheit' },
series: [{
showInLegend: false,
data: []
}],
plotOptions: {
line: { animation: false,
dataLabels: { enabled: true }
}
},
xAxis: {
type: 'datetime',
dateTimeLabelFormats: { second: '%H:%M:%S' }
},
yAxis: {
title: { text: 'fahrenheit (F)' }
},
credits: { enabled: false }
});
setInterval(function ( ) {
var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
if (this.readyState == 4 && this.status == 200) {
var x = (new Date()).getTime(),
y = parseFloat(this.responseText);
//console.log(this.responseText);
if(chartF.series[0].data.length > 50) {
chartF.series[0].addPoint([x, y], true, true, true);
} else {
chartF.series[0].addPoint([x, y], true, false, true);
}
}
};
xhttp.open("GET", "/fahrenheit", true);
xhttp.send();
}, 1000 ) ;

var chartH = new Highcharts.Chart({
chart:{ renderTo:'humidity-chart' },
title: { text: 'Humidity (%)' },
series: [{
showInLegend: false,
data: []
}],
plotOptions: {
line: { animation: false,
dataLabels: { enabled: true }
},
series: { color: '#18009c' }
},
xAxis: {
type: 'datetime',
dateTimeLabelFormats: { second: '%H:%M:%S' }
},
yAxis: {
title: { text: 'Humidity (%)' }
},
credits: { enabled: false }
});
setInterval(function ( ) {
var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
if (this.readyState == 4 && this.status == 200) {
var x = (new Date()).getTime(),
y = parseFloat(this.responseText);
//console.log(this.responseText);
if(chartH.series[0].data.length > 50) {
chartH.series[0].addPoint([x, y], true, true, true);
} else {
chartH.series[0].addPoint([x, y], true, false, true);
}
}
};
xhttp.open("GET", "/humidity", true);
xhttp.send();
}, 1000 ) ;
</script>
</html>)webpage";
