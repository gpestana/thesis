var sort_buckets = function(buckets) {
 buckets.sort(
  function(a, b) {
    if(a.price > b.price) return 1
    return -1
  }) 
}

var check_resources = function(workload, days, buckets, cb) {
  var possible_workload = 0
  buckets.forEach(function(bucket){
    possible_workload += bucket.events      
  })

  if(possible_workload * days < workload) {
    cb(false)
  } else {
    cb(true)
  }
}


var calculate_price = function(bucket, events) {
  bucket.final_price = bucket.price * events 
}



var run = function(workload, nr_days, buckets, cb) {
  check_resources(workload, nr_days, buckets, function(possible) {
    if(!possible) {
      cb(false)
    } else {

      var workload_left = workload
      sort_buckets(buckets)
  
      buckets.some(function(bucket) {
        var workload_left_tmp = workload_left
        var workload_after = workload_left_tmp -= bucket.events*nr_days

        if(workload_after <= 0) {
          //case last bucket
          calculate_price(bucket, workload_left)
          return true

        } else {
          //not last bucket
          calculate_price(bucket, bucket.events*nr_days)
          workload_left = workload_after
        }
      })
    }
  })

  cb(buckets)
}


exports.run = run
