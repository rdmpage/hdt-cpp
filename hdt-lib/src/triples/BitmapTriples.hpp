/*
 * BitmapTriples.hpp
 *
 *  Created on: 12/05/2011
 *      Author: mck
 */

#ifndef BITMAPTRIPLES_HPP_
#define BITMAPTRIPLES_HPP_

#include <Triples.hpp>
#include <HDTSpecification.hpp>

#include "../stream/WaveletStream.hpp"

#include <libcdsBasics.h>
#include <BitSequenceRG.h>
#include <BitString.h>

#include "../stream/AdjacencyList.hpp"
#include "TripleOrderConvert.hpp"

namespace hdt {

class BitmapTriples : public Triples {
private:
	ControlInformation controlInformation;
	HDTSpecification spec;
	StreamElements *streamY, *streamZ;
	cds_static::BitSequence *bitmapY, *bitmapZ;
	unsigned int numTriples;
	TripleComponentOrder order;
public:
	BitmapTriples();
	BitmapTriples(HDTSpecification &specification);
	virtual ~BitmapTriples();

	/**
	 * Returns a vector of triples matching the pattern
	 *
	 * @param triple
	 * @return
	 */
	IteratorTripleID *search(TripleID &triple);

	/**
	 * Calculates the cost to retrieve a specific pattern
	 *
	 * @param triple
	 * @return
	 */
	float cost(TripleID &triple);

	/**
	 * Returns the number of triples
	 *
	 * @return
	 */
	unsigned int getNumberOfElements();

	unsigned int size();

	/**
	 * Saves the triples
	 *
	 * @param output
	 * @return
	 */
	bool save(std::ostream &output, ControlInformation &controlInformation);

	/**
	 * Loads triples from a file
	 *
	 * @param input
	 * @return
	 */
	void load(std::istream &input, ControlInformation &controlInformation);

	void load(ModifiableTriples &triples);

	void populateHeader(Header &header, string rootNode);

	friend class BitmapTriplesSearchIterator;
	friend class MiddleWaveletIterator;
};

class BitmapTriplesSearchIterator : public IteratorTripleID {
private:
	BitmapTriples *triples;
	TripleID pattern;
	unsigned int patX, patY, patZ;

	AdjacencyList adjY, adjZ;
	unsigned int posY, posZ;
	unsigned int nextY, nextZ;
	unsigned int x, y, z;

	TripleID nextv;
	bool hasNextv;

	bool goThroughAll;

	void findFirst();
	void readTriple();
	void doFetch();

	void updateOutput();

public:
	BitmapTriplesSearchIterator(BitmapTriples *triples, TripleID &pat);

	bool hasNext();
	TripleID next();
};

class MiddleWaveletIterator : public IteratorTripleID {
private:
	BitmapTriples *triples;
	TripleID pattern;

	AdjacencyList adjY, adjZ;
	WaveletStream *wavelet;
	unsigned int patX, patY, patZ;
	unsigned int posY, posZ;
	unsigned int predicateOcurrence, numOcurrences;
	unsigned int nextY, nextZ;
	unsigned int x, y, z;

	TripleID nextv;
	bool hasNextv;

	void findFirst();
	void readTriple();
	void doFetch();

	void updateOutput();

public:
	MiddleWaveletIterator(BitmapTriples *triples, TripleID &pat);

	bool hasNext();
	TripleID next();
};

}



#endif /* BITMAPTRIPLES_HPP_ */
