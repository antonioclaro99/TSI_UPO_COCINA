# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Cursos(models.Model):
     _name = 'cocina.cursos'
     _description = 'cocina cursos'
     _rec_name='nombre'

     nombre = fields.Char(string="Nombre Curso", size=60, required=True, help="Nombre de nuestra curso")
     tipo = fields.Selection([('diseno', 'Cocina de diseño'),('lactosa','Para intolerantes a la lactosa'),('huevo','Para intolerantes al huevo'),('frutossecos','Para intolerantes a los frutos secos'),('marisco','Para intolerantes al marisco'),('gluten','Para celiacos')], 'Tipo')
     fechaInicio = fields.Datetime('Fecha inicio', help="Fecha de inicio de nuestro curso")
     fechaFin = fields.Datetime('Fecha fin', help="Fecha de finalizacion de nuestro curso")
     recetas_ids = fields.Many2many("cocina.recetas", string="Lista de recetas")
     precioCurso = fields.Float(string="Precio curso", compute='_compute_total')
    
     _sql_constraints = [('cursos_nombre_unique','UNIQUE (nombre)','El nombre debe ser único')]
     
     @api.constrains('recetas_ids', 'tipo')
     def intolerancia(self):
        for curso in self:
            for receta in curso.recetas_ids:
                for linea in receta.lineaingrediente_ids:
                    if linea.ingrediente_id.alergeno == curso.tipo:
                        mensaje = "La receta " + receta.nombre + " no es valida para este curso"
                        raise models.ValidationError(mensaje)
            
     
     
     @api.depends_context('recetas_ids', 'recetas_ids.precioReceta')
     def _compute_total(self):   
        for linea in self:
            precioActual = 0
            if linea.precioCurso != 0:
                precioActual = linea.precioCurso

            for receta in linea.recetas_ids:
                precioActual += receta.precioReceta
                
            linea.precioCurso = precioActual + (precioActual * 0.5) + 10