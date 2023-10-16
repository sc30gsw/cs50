document.addEventListener('DOMContentLoaded', () => {
  let count = 0
  const countDisplay = document.getElementById('counterValue')
  const btnPlus = document.getElementById('plus')
  const btnMinus = document.getElementById('minus')

  const updateDisplay = () => {
    countDisplay.textContent = count
  }

  btnPlus.addEventListener('click', () => {
    count++
    updateDisplay()
  })

  btnMinus.addEventListener('click', () => {
    count--
    updateDisplay()
  })

  updateDisplay()
})
