Class {
	#name : 'Board',
	#superclass : 'Object',
	#instVars : [
		'cells',
		'rows',
		'cols'
	],
	#category : 'LightsOut',
	#package : 'LightsOut'
}

{ #category : 'actions' }
Board >> blockForCell: aCell [
    ^ [ aCell toggle ].
]

{ #category : 'actions' }
Board >> clearBoard [
    cells do: [:row |
        row do: [:cell |
            cell morph ifNotNil: [ cell morph delete ]]].
]

{ #category : 'initialization' }
Board >> initializeBoard [
	| size cell morph thisCell |
	size := 5. "Tamaño del tablero 5x5, puedes cambiarlo"
	cells := Array new: size.

	1 to: size do: [:r |
		cells at: r put: (Array new: size).
		1 to: size do: [:c |
			cell := LightCell new.
			cell board: self; row: r; col: c; on: false.
			
			"crear un Morph para representarla"
			morph := Morph new.
			morph extent: 40@40; position: (r*45)@(c*45).
			morph color: Color gray.

			morph on: #mouseDown send: #value to: [
                self toggleAtRow: r col: c
            ].
			
			cell morph: morph.
			World addMorph: morph.
			
			(cells at: r) at: c put: cell.
		].
	].

]

{ #category : 'actions' }
Board >> toggleAtRow: r col: c [
    | deltas rr cc |
    deltas := { 0@0. -1@0. 1@0. 0@(-1). 0@1. }.
    deltas do: [:d |
        rr := r + d x.
        cc := c + d y.
        (rr between: 1 and: cells size) ifTrue: [
            (cc between: 1 and: ((cells at: rr) size)) ifTrue: [
                ((cells at: rr) at: cc) toggle
            ]].
    ].

]
