/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aaaa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:23:23 by xortega           #+#    #+#             */
/*   Updated: 2023/10/31 13:29:21 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>	

int main(void)
{
	char str[] = "(Verse 1) Spooky, scary skeletons Send shivers down your spine Shrieking skulls will shock your soul Seal your doom tonight (Chorus) Spooky, scary skeletons Speak with such a screech You'll shake and shudder in surprise When you hear these zombies shriek (Verse 2) We're so sorry, skeletons You're so misunderstood You only want to socialize But I don't think we should (Chorus) 'Cause spooky, scary skeletons Shout startling, shrilly screams They'll sneak from their sarcophagus And just won't leave you be (Verse 3) Spirits, supernatural Are shy, what's all the fuss? But bags of bones seem so unsafe It's semi-serious! (Chorus) Spooky, scary skeletons Are silly all the same They'll smile and scrabble slowly by And drive you so insane (Verse 4) Sticks and stones will break your bones They seldom let you snooze Spooky, scary skeletons Will wake you with a boo! (Chorus) Spooky, scary skeletons Send shivers down your spine Shrieking skulls will shock your soul Seal your doom tonight";
	int i;
	int a;
	
	i = 0;
	a = 0;
	//printf("%s", str);
	while (str[i])
	{
		if (str[i] == ' ')
		{
			if (a == 5)
				write(1, (str + i), 5);
			a = 0;
		}
		i++;
	}
}