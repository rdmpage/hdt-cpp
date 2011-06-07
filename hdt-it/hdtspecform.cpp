#include "hdtspecform.hpp"
#include "ui_hdtspecform.h"

#include <QtGui>

HDTSpecForm::HDTSpecForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HDTSpecForm)
{
    ui->setupUi(this);
}

HDTSpecForm::~HDTSpecForm()
{
    delete ui;
}

void HDTSpecForm::on_triplesTypeCombo_currentIndexChanged(int index)
{
    switch(index) {
    case 0:
        // BitmapTriples
        ui->streamXcombo->setEnabled(false);
        ui->streamYcombo->setEnabled(true);
        ui->streamZcombo->setEnabled(true);
        break;
    case 1:
        // TriplesList
        ui->streamXcombo->setEnabled(false);
        ui->streamYcombo->setEnabled(false);
        ui->streamZcombo->setEnabled(false);
        break;
    case 2:
        // PlainTriples
        ui->streamXcombo->setEnabled(true);
        ui->streamYcombo->setEnabled(true);
        ui->streamZcombo->setEnabled(true);
        break;
    case 3:
        // CompactTriples
        ui->streamXcombo->setEnabled(false);
        ui->streamYcombo->setEnabled(true);
        ui->streamZcombo->setEnabled(true);
        break;
    }
}

void HDTSpecForm::on_inputFileButton_clicked()
{
    QString file = QFileDialog::getOpenFileName(this,tr("Select Input RDF File"), tr("/Users/mck/workspace-cpp/hdt-lib/data"), tr("RDF Files(*)"), 0, 0 );
    ui->rdfInputFile->setText(file);
}

QString HDTSpecForm::getFileName()
{
    return ui->rdfInputFile->text();
}

std::string HDTSpecForm::getStreamType(int index) {
    switch(index) {
    case 0:
        // LogStream
        return hdt::HDTVocabulary::STREAM_TYPE_LOG;
    case 1:
        // IntegerStream
        return hdt::HDTVocabulary::STREAM_TYPE_INTEGER;
    case 2:
        // HuffmanStream
        return hdt::HDTVocabulary::STREAM_TYPE_HUFFMAN;
    case 3:
        // WaveletStream
        return hdt::HDTVocabulary::STREAM_TYPE_WAVELET;
    }
    return "";
}

void HDTSpecForm::fillHDTSpecification(hdt::HDTSpecification &hdt)
{
    hdt.set("header.type", hdt::HDTVocabulary::DICTIONARY_TYPE_PLAIN);
    hdt.set("dictionary.type", hdt::HDTVocabulary::DICTIONARY_TYPE_PLAIN);

    switch(ui->triplesTypeCombo->currentIndex()) {
    case 0:
        // BitmapTriples
        hdt.set("triples.type", hdt::HDTVocabulary::TRIPLES_TYPE_BITMAP);
        break;
    case 1:
        // TriplesList
        hdt.set("triples.type", hdt::HDTVocabulary::TRIPLES_TYPE_TRIPLESLIST);
        break;
    case 2:
        // PlainTriples
        hdt.set("triples.type", hdt::HDTVocabulary::TRIPLES_TYPE_PLAIN);
        break;
    case 3:
        // CompactTriples
        hdt.set("triples.type", hdt::HDTVocabulary::TRIPLES_TYPE_COMPACT);
        break;
    }

    if(ui->streamXcombo->isEnabled()) {
        hdt.set("stream.x", getStreamType(ui->streamXcombo->currentIndex()));
    }

    if(ui->streamYcombo->isEnabled()) {
        hdt.set("stream.y", getStreamType(ui->streamYcombo->currentIndex()));
    }

    if(ui->streamZcombo->isEnabled()) {
        hdt.set("stream.z", getStreamType(ui->streamZcombo->currentIndex()));
    }
}

hdt::RDFNotation HDTSpecForm::getNotation()
{
    switch(ui->rdfInputCombo->currentIndex()) {
    case 0:
        return hdt::N3;
    case 1:
        return hdt::TURTLE;
    case 2:
        return hdt::NTRIPLE;
    case 3:
        return hdt::XML;
    }
    return hdt::N3;
}
