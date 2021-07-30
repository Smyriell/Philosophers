/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 07:20:13 by smyriell          #+#    #+#             */
/*   Updated: 2021/07/30 00:37:54 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <semaphore.h>

void*	test()
{
	printf("Test from thread\n");
	sleep(3);
	printf("ending\n");
	return (0);
}

int main(int argc, char **argv)
{
    // pthread_t t1;
    // pthread_t t2;

    // if (pthread_create(&t1, NULL, &test, NULL) != 0)
	// 	return (1);
	// if (pthread_create(&t2, NULL, &test, NULL) != 0)
	// 	return (2);

    // sleep(10);
	printf("double = %lu\n", sizeof(double));
	printf("long long int = %lu\n", sizeof(long long int));
	printf("long int = %lu\n", sizeof(long));
	printf("int = %lu\n", sizeof(int));
		printf("LONG_MAX = %lu\n", __LONG_MAX__);
		printf("LONG_LONG_MAX = %lld\n", __LONG_LONG_MAX__);
    return (0);
}