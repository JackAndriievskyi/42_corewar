.name "BotFromKemerovo"
.comment "I had some problems
	I went too far
	Lower bottom of the lower hell
	It did not seem so deep to me,
	I called my mom,
	And my mother was right -
	She said: 'Immediately call
	Bot from Kemerovo.'

	He is stingy with words like De Niro
	Only the patient argues with him.
	You can not spend it on chaff,
	He knows the moves underground.
	The sky will fall to the ground,
	Stop growing grass -
	He will come and silently fix everything,
	A Bot form Kemerovo.

	Adam became a refugee,
	Abel got on mobile communication,
	Noah did not complete what he was building,
	He got drunk and feel face to face in the mud
	History of mankind
	It would not be so crooked,
	If they had guessed to contact
	With a Bot from Kemerovo.

	I was called from Kyiv,
	They called from Kathmandu
	Called from the opening of the plenum -
	I told them that I would not come.
	It will be necessary to drink at night two liters of water,
	So that in the mornign the head was whole -
	Because today I'm going to drink
	With a Bot from Kemerovo."

go:	live %42
	st r1,:go
	zjmp %:kemerovo

to:	st r1,:go

kemerovo:	ld :go,r1
			live %42
			fork %:go
			zjmp %:to
	