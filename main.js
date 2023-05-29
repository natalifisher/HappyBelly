// This was initially based on the information at
// https://dev.to/aws-heroes/worlds-simplest-synchronous-serverless-iot-dashboard-3ige
// The base code was then modified, added to, and made more complex in order to make the dashboard
// more visually pleasing and display and record the data we needed for the
// project
let humArr = [],
  weightArr = [],
  upArr = [],
  prevDate = -1;
let myHumidityChart = Highcharts.chart("humidityContainer", {
  title: {
    text: "Humidity",
  },

  subtitle: {
    text: "Humidity in the reservoir",
  },

  yAxis: {
    title: {
      text: "Humidity (%)",
    },
  },

  xAxis: {
    categories: upArr,
  },

  legend: {
    layout: "vertical",
    align: "right",
    verticalAlign: "middle",
  },

  plotOptions: {
    series: {
      label: {
        connectorAllowed: false,
      },
    },
  },
  series: [
    {
      name: "Humidity",
      data: [],
    },
  ],

  responsive: {
    rules: [
      {
        condition: {
          maxWidth: 500,
        },
        chartOptions: {
          legend: {
            layout: "horizontal",
            align: "center",
            verticalAlign: "bottom",
          },
        },
      },
    ],
  },
});
let myReservoirChart = Highcharts.chart("reservoirContainer", {
  title: {
    text: "Reservoir Fullness",
  },

  subtitle: {
    text: "Fullness of the reservoir",
  },

  yAxis: {
    title: {
      text: "Percent (%)",
    },
  },

  xAxis: {
    categories: upArr,
  },

  legend: {
    layout: "vertical",
    align: "right",
    verticalAlign: "middle",
  },

  plotOptions: {
    series: {
      label: {
        connectorAllowed: false,
      },
    },
  },
  series: [
    {
      name: "Weight",
      data: [],
    },
  ],

  responsive: {
    rules: [
      {
        condition: {
          maxWidth: 500,
        },
        chartOptions: {
          legend: {
            layout: "horizontal",
            align: "center",
            verticalAlign: "bottom",
          },
        },
      },
    ],
  },
});

let getData = function () {
  $.ajax({
    type: "GET",
    url: "https://cs147s3final.s3.us-east-2.amazonaws.com/finalKey", //example: https://mydatabucket.s3.amazonaws.com/myKey"
    dataType: "json",
    async: false,
    success: function (data) {
      console.log("data", data);
      drawChart(data);
    },
    error: function (xhr, status, error) {
      console.error("JSON error: " + status);
    },
  });
};

let drawChart = function (data) {
  let {
    humidity,
    resWeight,
    petWeight,
    age,
    breed,
    humidityWarning,
    reservoirWarning,
    foodEatenWarning,
    fallOverWarning,
    timestamps,
  } = data;

  const date = new Date(Number(timestamps));

  if (prevDate != -1 && prevDate.getTime() == date.getTime()) {
    return; //don't plot, same data
  }
  prevDate = date;
  upArr.push(date.toLocaleString("en-US"));
  humArr.push(Number(humidity));
  weightArr.push(Number(resWeight));

  //display pet biological information

  document.getElementById("age").innerHTML = "Age: fillhere";
  document.getElementById("age").innerHTML = document
    .getElementById("age")
    .innerHTML.replace("fillhere", age);
  document.getElementById("weight").innerHTML = "Weight: fillhere";
  document.getElementById("weight").innerHTML = document
    .getElementById("weight")
    .innerHTML.replace("fillhere", petWeight);
  document.getElementById("breed").innerHTML = "Breed: fillhere";
  document.getElementById("breed").innerHTML = document
    .getElementById("breed")
    .innerHTML.replace("fillhere", breed);

  //display warnings and alerts on screen

  document.getElementById("humidityWarning").innerHTML = ".";
  document.getElementById("humidityWarning").innerHTML = document
    .getElementById("humidityWarning")
    .innerHTML.replace(".", humidityWarning);

  document.getElementById("reservoirWarning").innerHTML = ".";
  document.getElementById("reservoirWarning").innerHTML = document
    .getElementById("reservoirWarning")
    .innerHTML.replace(".", reservoirWarning);

  // document.getElementById("foodEatenWarning").innerHTML = ".";
  // document.getElementById("foodEatenWarning").innerHTML = document
  //   .getElementById("foodEatenWarning")
  //   .innerHTML.replace(".", foodEatenWarning);

  document.getElementById("fallOverWarning").innerHTML = ".";
  document.getElementById("fallOverWarning").innerHTML = document
    .getElementById("fallOverWarning")
    .innerHTML.replace(".", fallOverWarning);

  myHumidityChart.series[0].setData(humArr, true);
  myReservoirChart.series[0].setData(weightArr, true);
};

let intervalTime = 5 * 1000; // 3 second interval polling, change as you like
setInterval(() => {
  getData();
}, intervalTime);
