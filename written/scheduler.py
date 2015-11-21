#!/usr/bin/python
def scheduler(buckets, days, nr_events):
	nr_events_left = nr_events
	final_prices = []
	sorted(buckets) #sorts according to price per event, from lowest to highest

	for bucket in buckets:
		nr_possible_ev_process = bucket['nr_ev_day'] * days 
		
		#ensures that no more events than the needed are processed
		nr_ev_process = nr_events_left if nr_possible_ev_process > nr_events_left \
			else nr_possible_ev_process

		price = bucket['price_ev'] * nr_ev_process
		final_prices.append(price)
		print bucket['name']+' processed '+ str(nr_ev_process)

		nr_events_left -= nr_ev_process
		if (nr_events_left <= 0):
			return sum(final_prices)

	return 'ERR: not enough machine processing power to process events before the deadline'

days = 100
nr_events = 1200000

bucket_1 = {
	'price_ev': 8.8*10**-8,
	'nr_ev_day': 40824/2,
	'name': 'ARM_LOW'
}

bucket_2 = {
	'price_ev': 2.6*10**-7,
	'nr_ev_day': 40824/2,
	'name': 'ARM_HIGH'
}

bucket_3 = {
	'price_ev': 2.4*10**-6,
	'nr_ev_day': 731289/2,
	'name': 'INTEL_LOW'
}

bucket_4 = {
	'price_ev': 7.2*10**-6,
	'nr_ev_day': 731289/2,
	'name': 'INTEL_HIGH'
}

result = scheduler([bucket_1, bucket_2, bucket_3, bucket_4], days, nr_events)
print result

