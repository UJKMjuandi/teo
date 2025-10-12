Class {
	#name : 'LightCell',
	#superclass : 'Object',
	#instVars : [
		'on',
		'morph',
		'row',
		'col',
		'board'
	],
	#category : 'LightsOut',
	#package : 'LightsOut'
}

{ #category : 'accessing' }
LightCell >> board [
	^ board 
]

{ #category : 'accessing' }
LightCell >> board: aBoard [
	board := aBoard 
	
]

{ #category : 'actions' }
LightCell >> clicked [ 
	board toggleAtRow: row col: col.

]

{ #category : 'accessing' }
LightCell >> col [
	 ^ col
]

{ #category : 'accessing' }
LightCell >> col: aCol [
	col := aCol 
]

{ #category : 'initialization' }
LightCell >> initializeAtRow: r col: c board: b [
	row := r. 
	col := c.
	board := b.
	on := false.
	morph := Morph new
		color: Color gray;
		extent: 50@50.
	morph on: #mouseUp send: #clicked to: self
		 
	
	
]

{ #category : 'accessing' }
LightCell >> morph [
	^ morph
]

{ #category : 'accessing' }
LightCell >> morph: aMorph [
	morph := aMorph
]

{ #category : 'accessing' }
LightCell >> on [
	^ on
]

{ #category : 'accessing' }
LightCell >> on: aBoolean [
	on := aBoolean
]

{ #category : 'accessing' }
LightCell >> row [
	^ row
]

{ #category : 'accessing' }
LightCell >> row: aRow [
	row := aRow 
]

{ #category : 'actions' }
LightCell >> toggle [
	on := on not.
	morph color: (on ifTrue: [Color yellow] ifFalse: [Color gray]).
]
