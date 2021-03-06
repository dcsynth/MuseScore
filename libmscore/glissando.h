//=============================================================================
//  MuseScore
//  Music Composition & Notation
//
//  Copyright (C) 2008-2011 Werner Schweer
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2
//  as published by the Free Software Foundation and appearing in
//  the file LICENCE.GPL
//=============================================================================

#ifndef __GLISSANDO_H__
#define __GLISSANDO_H__

#include "element.h"
#include "line.h"
#include "property.h"

namespace Ms {

// the amount of white space to leave before a system-initial chord with glissando
static const qreal      GLISS_STARTOFSYSTEM_WIDTH = 4;      // in sp

class Glissando;
class Note;
enum class GlissandoType;

//---------------------------------------------------------
//   @@ GlissandoSegment
//---------------------------------------------------------

class GlissandoSegment : public LineSegment {
   public:
      GlissandoSegment(Score* s) : LineSegment(s)           {}
      Glissando* glissando() const                          { return (Glissando*)spanner(); }
      virtual ElementType type() const override             { return ElementType::GLISSANDO_SEGMENT; }
      virtual GlissandoSegment* clone() const override      { return new GlissandoSegment(*this); }
      virtual void draw(QPainter*) const override;
      virtual void layout() override;

      virtual QVariant getProperty(P_ID id) const override;
      virtual bool setProperty(P_ID propertyId, const QVariant&) override;
      virtual QVariant propertyDefault(P_ID id) const override;
      virtual PropertyFlags& propertyFlags(P_ID) override;
      virtual void setPropertyFlags(P_ID id, PropertyFlags f) override;
      virtual StyleIdx getPropertyStyle(P_ID) const override;
      };

//---------------------------------------------------------
//   Glissando
//---------------------------------------------------------

class Glissando : public SLine {
      QString _text;
      GlissandoType _glissandoType;
      GlissandoStyle _glissandoStyle;

      M_PROPERTY(QString, fontFace, setFontFace)
      M_PROPERTY(qreal, fontSize, setFontSize)
      M_PROPERTY(bool, showText, setShowText)
      M_PROPERTY(bool, playGlissando, setPlayGlissando)
      M_PROPERTY(bool, fontBold, setFontBold)
      M_PROPERTY(bool, fontItalic, setFontItalic)
      M_PROPERTY(bool, fontUnderline, setFontUnderline)

   public:
      Glissando(Score* s);
      Glissando(const Glissando&);

      static Note* guessInitialNote(Chord* chord);
      static Note* guessFinalNote(Chord* chord);

      // overriden inherited methods
      virtual Glissando* clone() const override     { return new Glissando(*this);   }
      virtual ElementType type() const override     { return ElementType::GLISSANDO; }
      virtual LineSegment* createLineSegment() override;
      virtual void scanElements(void* data, void (*func)(void*, Element*), bool all=true) override;
      virtual void layout() override;
      virtual void write(XmlWriter&) const override;
      virtual void read(XmlReader&) override;

      // Glissando specific methods
      GlissandoType glissandoType() const      { return _glissandoType;  }
      void setGlissandoType(GlissandoType v)   { _glissandoType = v;     }
      GlissandoStyle glissandoStyle() const    { return _glissandoStyle; }
      void setGlissandoStyle(GlissandoStyle s) { _glissandoStyle = s;    }
      QString text() const                     { return _text;           }
      void setText(const QString& t)           { _text = t;              }

      // property/style methods
      virtual QVariant getProperty(P_ID propertyId) const override;
      virtual bool     setProperty(P_ID propertyId, const QVariant&) override;
      virtual QVariant propertyDefault(P_ID) const override;
      virtual PropertyFlags& propertyFlags(P_ID) override;
      virtual StyleIdx getPropertyStyle(P_ID) const override;

      virtual void styleChanged() override;
      };


}     // namespace Ms

#endif

