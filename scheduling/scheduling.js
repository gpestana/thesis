/*
  Fixed vars: 
    nr_series: days to run
    buckets 
*/

var buckets = [{"price":1},{"price":4},{"price":2}]

var init  = function() {
  var buck1 = {
    "size": 0,
    "units": 0,
    "price": 0
  }

  buckets.push(buck1)
  //... 
}

var sort_buckets = function() {
 buckets.sort(
  function(a, b) {
    if(a.price > b.price) return 1
    return -1
  }) 
}

var run = function(workload, nr_series) {

  //init()
  check_resources(workload, nr_series) //check if there are enough buckets for workload
  sort_buckets()

  var remainder_worload = workload

  buckets.forEach(function(bucket) {
    calculate_price()
    remainder_workload -= bucket.units*nr_series)
    if(remainder_workload <= 0) return   
  }) 
}


run(1200000, 2)
