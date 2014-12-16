var scheduling = require('./scheduling')

var days = 2
var workload = 120000

var bucket_1 = {
  "price": Math.pow(8.8, -8),
  "events": 20412,
  "final_price": 0
}

var bucket_2 = {
  "price": Math.pow(2.6, -7),
  "events": 20412,
  "final_price": 0
}

 var bucket_3 = {
  "price": Math.pow(2.4, -6),
  "events": 36564,
  "final_price": 0
}

var bucket_4 = {
  "price": Math.pow(7.2, -6),
  "events": 36564,
  "final_price": 0
}

var buckets = [bucket_1, bucket_2, bucket_3, bucket_4]


scheduling.run(workload, days, buckets, function(bucks, err) {
  var total = 0
  bucks.forEach(function(b){
    total += b.final_price
  })
  
  console.log("Final Price: "+total+ " euros")
})
