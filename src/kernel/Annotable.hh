/*-
 * Copyright (C) 2010-2014, Centre National de la Recherche Scientifique,
 *                          Institut Polytechnique de Bordeaux,
 *                          Universite de Bordeaux.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#ifndef KERNEL_ANNOTABLE_HH
#define KERNEL_ANNOTABLE_HH

#include <string>
#include <vector>

#include <kernel/Annotation.hh>
#include <utils/unordered11.hh>

/* ***************************************************/
/**
 * \brief  Interface for annotable objects
 */
/* ***************************************************/
class Annotable
{
public:
  typedef std::string AnnotationId;
  typedef std::unordered_map<AnnotationId,Annotation*> AnnotationMap;

  Annotable(const AnnotationMap *o = 0);
  Annotable(AnnotationMap &o);

  /*! \brief Copy constructor */
  Annotable(const Annotable &o);
  /*! \brief Destructor */
  virtual ~Annotable();

  /*! \brief get annotations. Renamed this method in order to
   * lower the number of name conflicts on methods such as begin().
   * That's why the inheritance on std::unordered_map is private */
  const AnnotationMap *get_annotations() const;
  /*! \brief get a specific annotation. */
  Annotation *get_annotation(const AnnotationId &id) const;
  /*! \brief get a specific annotation. */
  Annotation *get_annotation(const char *id) const;
  /*! \brief get a vector of sorted annotation ids to help determinism */
  std::vector<AnnotationId> *get_sorted_annotation_ids() const;

  /*! \brief add an annotation. Cf. previous remark */
  void add_annotation(const AnnotationId &id, Annotation *a);
  /*! \brief add an annotation. Cf. previous remark */
  void add_annotation(const char id[], Annotation *a);
  /*! \brief returns true if contains at least one annotation */
  bool is_annotated() const;
  /*! \brief returns true if contains an annotation of id \code id */
  bool has_annotation(const AnnotationId &id) const;

  /*! \brief returns true if contains an annotation of id \code id */
  bool has_annotation(const char *id) const;

  /*! \brief delete an annotation of id \code id */
  void del_annotation(const char *id);
  /*! \brief delete an annotation of id \code id  */
  void del_annotation(const AnnotationId &id);

  void output_annotations (std::ostream &) const;

private:
  void copy_from_map(const AnnotationMap &o);

  AnnotationMap amap;
};

#endif /* KERNEL_ANNOTABLE_HH */
