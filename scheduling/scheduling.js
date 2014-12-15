var buckets = [
  {"price":1, "units": 10},
  {"price":3, "units": 10},
  {"price":6,  "units": 23},
  {"price":10, "units": 23}
]

var sort_buckets = function() {
 buckets.sort(
  function(a, b) {
    if(a.price > b.price) return 1
    return -1
  }) 
}

var check_resources = function(workload, nr_series, cb) {
  cb()
}

var calculate_price = function(bucket, units) {
  bucket.final_price = bucket.price * units 
}



var run = function(workload, nr_series, buckets, cb) {

  check_resources(workload, nr_series, function(res) {
    if(res) {
      cb(null, "Machine resources are not enough to meet deadline")
      return
    } else {

      var workload_left = workload
      sort_buckets()

      buckets.forEach(function(bucket) {
        var units_series = bucket.units * nr_series 
        
        if(workload_left -= units_series <= 0) {
          var final_events = workload_left
          calculate_price(bucket, workload_left) 
          //cb(buckets)
          return
        } else {
          calculate_price(bucket, units_series)
        }
      })
      cb(buckets)
    }
  })
}



run(30, 1, buckets, function(final_buckets, err){
  if(err) console.log(err)
  else {
    console.log(final_buckets)   
  }
})


