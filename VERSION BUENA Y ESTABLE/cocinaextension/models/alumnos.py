# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Alumnos(models.Model):
    _name ='cocinaextension.alumnos'
    _inherit = 'cocina.personas'

    id_alumno = fields.Integer("idAlumno")
    descuento = fields.Boolean("Descuento")

    cursos_ids = fields.Many2many("cocina.cursos",string="Cursos Confirmados")
    precioTotal= fields.Float(compute="_compute_precioTotalAlumno")

    @api.depends('cursos_ids')
    def _compute_precioTotalAlumno(self):
        for alumno in self:
            for curso in alumno.cursos_ids:
                alumno.precioTotal+=curso.precioCurso
            if alumno.descuento == True:
                alumno.precioTotal=alumno.precioTotal * 0.80