#!/usr/bin/python

def scheduler(buckets, days, nr_events):
	nr_events_left = nr_events
	final_prices = []

	buckets.sort() #sorts according to price per event, from lowest to highest

	for bucket in buckets
		nr_ev_process = bucket.nr_ev_day * days 
		price = bucket.price_ev * nr_ev_process
		final_prices.push(price)
		nr_events_left -= nr_ev_process

		if (nr_ev_process <= 0)
			return final_prices.sum()

	return 'ERR: not enough machine processing power to the deadline'



days = 2
nr_events = 40

bucket_1 = {
	'nr_ev_days': 10;
	'price_ev': 0.1
}

bucket_2 = {
	'nr_ev_days': 75;
	'price_ev': 3
}

result = scheduler([bucket_1, bucket_2], days, nr_events)


