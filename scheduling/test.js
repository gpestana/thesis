var test    = require('tape'),
scheduling  = require('./scheduling.js')

//scheduling(workload, nr_days, buckets, cb)

 
test('bucks_1', function(t) {

var buckets = [ 
  {"price":1, "events": 2, "final_price": 0},
  {"price":5, "events": 8, "final_price": 0}]

  scheduling.run(2, 1, buckets, function(bucks, err){
    t.equal(bucks[0].final_price, 2, 'only one event was run')
    t.equal(bucks[1].final_price, 0, 'no event was running in this bucket')
  })
  scheduling.run(3, 1, buckets, function(bucks, err){
    t.equal(bucks[0].final_price, 2, 'only one event was run')
    t.equal(bucks[1].final_price, 5, 'no event was running in this bucket')
  })

  t.end() 
})


test('bucks_no_resources', function(t) {

var buckets = [ 
  {"price":1, "events": 2, "final_price": 0},
  {"price":5, "events": 8, "final_price": 0}]

  scheduling.run(12, 1, buckets, function(buck){
    //t.equal(buck[0].final_price, 0, "not enough resources to process events")  
  })

  t.end()
})
