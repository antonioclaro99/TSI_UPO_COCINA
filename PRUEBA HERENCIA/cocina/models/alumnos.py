# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Alumnos(models.Model):
    _name ='cocina.alumnos'
    _inherit = 'base.personas'

    id_alumno = fields.Integer("idAlumno")
    descuento = fields.Boolean("Descuento")

    cursos_ids = fields.Many2many("cocina.cursos",string="Cursos Confirmados")
    precioTotal= fields.Float(compute="_compute_precioTotalAlumno")

    @api.depends('cursos_ids')
    def _compute_precioTotalAlumno(self):
        for alumno in self:
            alumno.precioTotal=0
            for curso in alumno.cursos_ids:
                alumno.precioTotal+=curso.precioCurso
            if alumno.descuento == True:
                alumno.precioTotal=alumno.precioTotal * 0.80